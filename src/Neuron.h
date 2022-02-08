//
// Created by Kaeden on 1/30/22.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H
#pragma once

#include "List.h"

class Neuron
{
public:
	// Declares output
	float output;
	float unactivatedOutput{};

private:
	// Declare inputs, weights, and bias of the neuron
    bool DEBUG_MODE;
	List inputs;
	List weights;
	float neuronError{};
	float bias = 0.0;

private:
	// Note: Rectified Linear Unit (ReLU)
	static float ReLU_ActivationFunc(float a);

	// Note: Sigmoid
	static float Sigmoid_ActivationFunc(float a);

	// Note: Derivative of sigmoid
	static float Sigmoid_Derivative(float a);

	static float MSE_Derivative(float output, float answer);

public:
    void setInputs(const List& newInputs);
	void setInputs(const std::vector<float>& newInputs);

	void forceUpdateOutputs(float newOutputs);

	// Because our cost function is MSE, we use the
	// derivative of MSE to get our error 
	float getErrorFromAnswer(float answer);

    float getErrorFromNextLayer(List next_errors, List next_weights);
	float getErrorFromNextLayer(std::vector<float> next_errors, std::vector<float> next_weights);

	List getWeights() const;

	float getBias() const;

	static float sumInputs(List& matrix);

	void applyBiasError(float error);

	void applyWeightError(float error);

public:
	float getOutput();

public:
	// Constructor of bias, inputs, weights, and calculating the output
	Neuron(List inputs, List weights, float bias, bool DEBUG_MODE = true);
    Neuron(std::vector<float> inputs, std::vector<float> weights, float bias, bool DEBUG_MODE = true);

};

#endif //NEURALNETWORK_NEURON_H
