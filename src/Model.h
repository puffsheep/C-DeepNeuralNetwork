//
// Created by Kaeden on 1/30/22.
//

/*
==========================================
1) Create layers -> Send size then inputs
2) Softmax final layer outputs
3) Calculate error in each layer
4) Apply error to each layer
5) Send new input data
6) Repeat
==========================================
*/

#ifndef NEURALNETWORK_MODEL_H
#define NEURALNETWORK_MODEL_H
#pragma once

#include "MyNN.h"

class Model {
public:
    bool DEBUG_MODE;

private:
	std::vector<Layer> layers;

    // Takes array-like type (List or std::vector)
    template <typename TData>
    void train(const TData& data, const TData& answers);

public:
    Model(int model_size, std::vector<int> model_specs, const List& data, bool DEBUG_MODE = false);
    Model(int model_size, std::vector<int> model_specs, const std::vector<float>& data, bool DEBUG_MODE = false);

    void train_model(const List& data, const List& answers);
    void train_model(const List& data, const List& answers, int iterations);
	void train_model(const std::vector<float>& data, const std::vector<float>& answers);
    void train_model(const std::vector<float>& data, const std::vector<float>& answers, int iterations);
    void train_model(std::vector<std::vector<float>> data, std::vector<std::vector<float>> answers, int iterations, int sampleStep = 1);
    void train_model(Matrix& data, Matrix& answers, int iterations, int sampleStep = 1);

	void run_model(const std::vector<float>& data);
    void run_model(const std::vector<std::vector<float>>& data, int sampleStep = 1);
    void run_model(Matrix data, int sampleStep = 1);

    static void printLayer(Layer &layer);
};

#endif //NEURALNETWORK_MODEL_H
