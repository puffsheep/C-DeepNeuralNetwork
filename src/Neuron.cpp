#include <vector>
#include <cmath>
#include <iostream>

#include "List.h"
#include "Neuron.h"

// Note: Rectified Linear Unit (ReLU)
float Neuron::ReLU_ActivationFunc(float a)
{
	return fmax(a, 0);
}

// Note: Sigmoid
float Neuron::Sigmoid_ActivationFunc(float a)
{
	return (1 / (1 + exp(-a)));
}

// Note: Derivative of sigmoid
float Neuron::Sigmoid_Derivative(float a)
{
	//return (-exp(a)/((1+exp(a))*(1+exp(a))));
	//return (1 / (1 + exp(-a))) * ( 1 - (1 / (1 + exp(-a))));
	return output * (1 - output);
}

float Neuron::MSE_Derivative(float output, float answer)
{
	return (output - answer);
}

void Neuron::setInputs(const List& newInputs)
{
    this->inputs = newInputs;
}

void Neuron::setInputs(const std::vector<float>& newInputs)
{
	this->inputs = newInputs;
}

void Neuron::forceUpdateOutputs(float newOutputs)
{
	output = newOutputs;
}

// Because our cost function is MSE, we use the
// derivative of MSE to get our error
float Neuron::getErrorFromAnswer(float answer)
{
	neuronError = 0;
	float cost_derivative = MSE_Derivative(output, answer);
	float error = cost_derivative * Sigmoid_Derivative(unactivatedOutput);

    if(DEBUG_MODE) {
        std::cout << "Output: " << output << std::endl;
        std::cout << "Answer: " << answer << std::endl;
    }

	neuronError = error;

	return neuronError;
}

float Neuron::getErrorFromNextLayer(List next_errors, List next_weights)
{
    float error = 0;
    for(int neuron=0; neuron<next_errors.size(); neuron++)
    {
        error += (next_errors[neuron] * next_weights[neuron]) * Sigmoid_Derivative(unactivatedOutput);
    }
    neuronError = error;
    return neuronError;
}

float Neuron::getErrorFromNextLayer(std::vector<float> next_errors, std::vector<float> next_weights)
{
	float error = 0;
	for(int neuron=0;neuron<next_errors.size();neuron++)
	{
		error += (next_errors[neuron] * next_weights[neuron]) * Sigmoid_Derivative(unactivatedOutput);
	}
	neuronError = error;
	return neuronError;
}

List Neuron::getWeights() const {
	return weights;
}

float Neuron::getBias() const {
	return bias;
}

float Neuron::sumInputs(List& list)
{
	float inputSum = 0;
	for(float i : list)
	{
		inputSum += i;
	}

	return inputSum;
}

void Neuron::applyBiasError(float error)
{
    /*if(DEBUG_MODE)
	    //std::cout << "Bias: " << bias << std::endl;*/

    bias -= error;

    /*if(DEBUG_MODE)
	    std::cout << "Bias modified: " << bias << std::endl;*/
}

void Neuron::applyWeightError(float error)
{	
	for(int i = 0; i < weights.size(); i++) {
		if(DEBUG_MODE)
		    std::cout << "Weight delta: " << inputs[i] * error << std::endl;

		weights[i] -= inputs[i] * error;
	}
}

float Neuron::getOutput()
{
	// Initialize the output vector
	float neuron_output;

	// Checks if shape is the same
	if(inputs.size() == weights.size())
	{
			neuron_output = 0;

			// Find dot product of inputs & weights
			// (Technically Hadamard product but with each output transposed)
			for(int i = 0; i < inputs.size(); i++)
			{
				neuron_output += inputs[i] * weights[i];
			}

			// Add bias to output
			neuron_output += bias;

			unactivatedOutput = neuron_output;

			// MARK: Activation Function Rectified Linear Unit (ReLU)
			neuron_output = Sigmoid_ActivationFunc(neuron_output);
	}
	else
	{
		printf("Weights size: %lu \n", weights.size());
		printf("Input size: %lu \n", inputs.size());
		printf("Error: Inputs and Weights are unequal. \n");
        throw std::invalid_argument("Inputs and weights are unequal");
	}

	this->output = neuron_output;
	return neuron_output;
}

// Constructor of bias, inputs, weights, and calculating the output
Neuron::Neuron(List inputs, List weights, float bias, bool DEBUG_MODE)
{
    this->DEBUG_MODE = DEBUG_MODE;
	this->bias = bias;
	this->inputs = std::move(inputs);
	this->weights = std::move(weights);
	this->output = getOutput();
}

Neuron::Neuron(std::vector<float> inputs, std::vector<float> weights, float bias, bool DEBUG_MODE)
{
    this->DEBUG_MODE = DEBUG_MODE;
    this->bias = bias;
    this->inputs = std::move(inputs);
    this->weights = std::move(weights);
    this->output = getOutput();
}
