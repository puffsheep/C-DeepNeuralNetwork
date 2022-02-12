#include <vector>
#include <cmath>
#include <iostream>

#include "Neuron.h"
#include "Utility.h"
#include "List.h"
#include "Layer.h"

// Maybe we should store this...
List Layer::getLayerWeights(int neuron) const {
    std::vector<float> n_weights;
    for(auto& n : layer) {
    	n_weights.push_back(n.getWeights()[neuron]);
    }

    return n_weights;
}

List Layer::getRandomWeights(size_t previousLayerSize)
{
	std::vector<float> randomWeightsArray;
	randomWeightsArray.reserve(previousLayerSize);
    for(int weightIndex = 0; weightIndex < previousLayerSize; weightIndex++)
	{
		randomWeightsArray.push_back(getRandomNumber(1, 10000));
	}
	return randomWeightsArray;
}

void Layer::AddNeuronToLayer(Neuron& neuron)
{
	this->layer.push_back(neuron);
	this->layer_outputs.push_back(neuron.output);
	this->unactivated_layer_outputs.push_back(neuron.unactivatedOutput);
}

void Layer::InitializeNeurons(size_t previousLayerSize)
{
	for(int neuronIndex = 0; neuronIndex < layerSize; neuronIndex++)
	{
		Neuron neuron(inputs, getRandomWeights(previousLayerSize), (float)1.0, DEBUG_MODE);

		AddNeuronToLayer(neuron);
	}
}

// Initial layer constructor
Layer::Layer(int layerSize, const List& inputs, bool DEBUG_MODE)
{
    this->DEBUG_MODE = DEBUG_MODE;
    this->inputs = inputs;
    this->layerSize = layerSize;
    size_t previousLayerSize = inputs.size();

    InitializeNeurons(previousLayerSize);

}

Layer::Layer(int layerSize, const std::vector<float>& inputs, bool DEBUG_MODE)
{
    this->DEBUG_MODE = DEBUG_MODE;
	this->inputs = inputs;
	this->layerSize = layerSize;
	size_t previousLayerSize = inputs.size();

	InitializeNeurons(previousLayerSize);

}

// Subsequent layer constructor
Layer::Layer(int layerSize, const Layer& previousLayer, bool DEBUG_MODE)
{
    this->DEBUG_MODE = DEBUG_MODE;
	this->inputs = previousLayer.layer_outputs;
	this->layerSize = layerSize;

	InitializeNeurons(previousLayer.layerSize);

}

void Layer::runLayerWithInput(const std::vector<float>& layer_inputs)
{
	this->inputs = layer_inputs;

	this->layer_outputs.clear();
	this->unactivated_layer_outputs.clear();

	for(auto& neuron : layer) {
		neuron.setInputs(inputs);
		layer_outputs.push_back(neuron.getOutput());
	}
}

void Layer::runLayerWithInput(const List& layer_inputs)
{
    this->inputs = layer_inputs;

    this->layer_outputs.clear();
    this->unactivated_layer_outputs.clear();

    for(auto& neuron : layer) {
        neuron.setInputs(inputs);
        layer_outputs.push_back(neuron.getOutput());
    }
}

void Layer::runLayerWithLayer(const Layer& previousLayer)
{
	this->inputs = previousLayer.layer_outputs;

	this->layer_outputs.clear();
	this->unactivated_layer_outputs.clear();

	for(auto& neuron : layer) {
		neuron.setInputs(inputs);
		layer_outputs.push_back(neuron.getOutput());
	}

}

// Mean squared error (MSE) loss function
// This function will find the average loss for several batches
void Layer::calculateLoss(const std::vector<float>& yActual)
{
	float totalLoss = 0.0;
	for(int x = 0; x < layer_outputs.size(); x++)
	{
		float deltaY = yActual[x] - layer_outputs[x];
		totalLoss += deltaY * deltaY;
	}
	totalLoss = totalLoss / (2 * layer_outputs.size());
	loss = totalLoss;
}

// Get initial error
void Layer::calculateErrorFromAnswer(const List& yActual)
{
	layer_errors.clear();
	// Catch error of differing number of answers to outputs
	if(yActual.size() != layerSize) {
		printf("Number of answers does not match the number of outputs! \n");
        throw std::invalid_argument("Unable to evaluate " + std::to_string(yActual.size()) + " answers and " + std::to_string(layerSize) + " outputs");
	}

	List neuronAnswers = yActual;
	for(int neuron=0; neuron<layerSize; neuron++)
	{
		float neuronErrors = layer[neuron].getErrorFromAnswer(neuronAnswers[neuron]);
		layer_errors.push_back(neuronErrors);
	}
}

void Layer::calculateErrorFromAnswer(const std::vector<float>& yActual)
{
    layer_errors.clear();
    // Catch error of differing number of answers to outputs
    if(yActual.size() != layerSize) {
        printf("Number of answers does not match the number of outputs! \n");
        throw std::invalid_argument("Unable to evaluate " + std::to_string(yActual.size()) + " answers and " + std::to_string(layerSize) + " outputs");
    }

    List neuronAnswers = yActual;
    for(int neuron=0; neuron<layerSize; neuron++)
    {
        float neuronErrors = layer[neuron].getErrorFromAnswer(neuronAnswers[neuron]);
        layer_errors.push_back(neuronErrors);
    }
}

void Layer::calculateErrorFromNextLayer(const Layer& nextLayer)
{
	layer_errors.clear();

	for(int neuron=0; neuron<layerSize; neuron++)
	{
		float neuronErrors = layer[neuron].getErrorFromNextLayer(nextLayer.layer_errors, nextLayer.getLayerWeights(neuron));
		layer_errors.push_back(neuronErrors);
	}
    if(DEBUG_MODE)
	    printVector(layer_errors);
}

void Layer::printLoss(std::vector<float>& answers)
{
    if(DEBUG_MODE) {
        calculateLoss(answers);
        printf("Loss: %f \n", loss);
    }
}

// Returns the value of neuron 0
float Layer::getOutput() {
	return layer[0].getOutput();
}

float Layer::sumError(List& list)
{
	float errorSum = 0;
	for(float i : list)
	{
		errorSum += i;
	}
	return errorSum;
}

void Layer::applyErrorsToLayer()
{		
	for(int neuron=0;neuron<layerSize;neuron++)
	{
		layer[neuron].applyWeightError(layer_errors[neuron]);
		layer[neuron].applyBiasError(layer_errors[neuron]);
	}
}

// Mean squared error (MSE) loss function
// This function will separate each batch into an array
void Layer::calculateLossBySeparateBatch(std::vector<float>& yActual)
{
	for(int x = 0; x < layer_outputs.size(); x++)
	{
		float deltaY = yActual[x] - layer_outputs[x];
		loss += 0.5 * pow(deltaY, 2);
	}
}

// Exponential normalized output values
// THIS WILL OVERRIDE ACTIVATED VALUES
void Layer::softmaxOutputs()
{
	float expSum = 0;
	// Calculates the exponential value for each output in each batch
	for(float & layer_output : layer_outputs)
	{
		// In order to limit our exponentiation, we want to
		// subtract the max output value from each batch before
		// plugging it into the exponential function
		float expOut = exp(layer_output - getMax(layer_outputs));
		layer_output = expOut;
		expSum += expOut;
	}
	// Normalizes the outputs by dividing by the sum of the outputs
	// The sum of these new outputs should add up to 1.0
	for(float & layer_output : layer_outputs)
	{
		layer_output /= expSum;
	}

	List outputs_T;
	outputs_T = layer_outputs;

	std::cout << "softmaxOutputs: " << std::endl;
	printVector(outputs_T);

	for(int neuronToUpdate=0;neuronToUpdate<outputs_T.size();neuronToUpdate++)
	{
		layer[neuronToUpdate].forceUpdateOutputs(outputs_T[neuronToUpdate]);
	}
	printf("%lu outputs have been exponentiated and normalized. \n", layer_outputs.size());
}
