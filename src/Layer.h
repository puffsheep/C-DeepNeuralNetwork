//
// Created by Kaeden on 1/30/22.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H
#pragma once

class Layer
{
public: // CHANGE BACK TO PRIVATE AFTER TESTING
    int layerSize;
    bool DEBUG_MODE;
	std::vector<Neuron> layer;
	List inputs;

public:
	List layer_errors;
    List unactivated_layer_outputs;
    List layer_outputs;
	float loss = 0;

private:
	// Maybe we should store this...
	List getLayerWeights(int neuron) const;

	static List getRandomWeights(size_t previousLayerSize);

	void AddNeuronToLayer(Neuron& neuron);

	void InitializeNeurons(size_t previousLayerSize);

public:
	// Initial layer constructor
    Layer(int layerSize, const List &inputs, bool DEBUG_MODE);
	Layer(int layerSize, const std::vector<float>& inputs, bool DEBUG_MODE = true);

	// Subsequent layer constructor
	Layer(int layerSize, const Layer& previousLayer, bool DEBUG_MODE = true);

	void runLayerWithInput(const std::vector<float>& inputs);
    void runLayerWithInput(const List &inputs);

	void runLayerWithLayer(const Layer& previousLayer);

	// Mean squared error (MSE) loss function 
	// This function will find the average loss for several batches
	void calculateLoss(const std::vector<float>& yActual);

	// Get initial error
	void calculateErrorFromAnswer(const List& yActual);
    void calculateErrorFromAnswer(const std::vector<float>& yActual);

	void calculateErrorFromNextLayer(const Layer& nextLayer);

	void printLoss(std::vector<float>& answers);

	// Returns the value of neuron 0
	float getOutput();

	static float sumError(List& matrix);

	void applyErrorsToLayer();

	// Mean squared error (MSE) loss function 
	// This function will separate each batch into an array
	void calculateLossBySeparateBatch(std::vector<float>& yActual);

	// Exponential normalized output values
	// THIS WILL OVERRIDE ACTIVATED VALUES
	void softmaxOutputs();
};

#endif //NEURALNETWORK_LAYER_H
