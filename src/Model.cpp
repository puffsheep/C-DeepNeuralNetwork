#include "MyNN.h"

#include "Model.h"
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

Model::Model(int model_size, std::vector<int> model_specs, const List& data, bool DEBUG_MODE) {
    this->DEBUG_MODE = DEBUG_MODE;

    // Used to create the first input layer
    layers.emplace_back(Layer(model_specs[0], data, DEBUG_MODE));
    Layer prev_layer = layers[0];

    // Used to create layers after first one
    for(int layer = 1; layer < model_size; layer++) {
        layers.emplace_back(Layer(model_specs[layer], prev_layer, DEBUG_MODE));
        prev_layer = layers[layer];
    }
}

Model::Model(int model_size, std::vector<int> model_specs, const std::vector<float>& data, bool DEBUG_MODE) {
    this->DEBUG_MODE = DEBUG_MODE;

	// Used to create the first input layer
	layers.emplace_back(Layer(model_specs[0], data, DEBUG_MODE));
	Layer prev_layer = layers[0];

	// Used to create layers after first one
	for(int layer = 1; layer < model_size; layer++) {
		layers.emplace_back(Layer(model_specs[layer], prev_layer, DEBUG_MODE));
		prev_layer = layers[layer];
	}
}

template <typename TData>
void Model::train(const TData& data, const TData& answers) {
    // 1. Start by running layers

    // Run input layer with data
    layers[0].runLayerWithInput(data);
    Layer prev_layer = layers[0];

    // Run other layers
    for(int layer = 1; layer < layers.size(); layer++) {
        layers[layer].runLayerWithLayer(prev_layer);
        prev_layer = layers[layer];
    }

    // 2. Calculate layer errors
    layers[layers.size() - 1].calculateErrorFromAnswer(answers);
    if(DEBUG_MODE) {
        std::cout << "Error 1: |" << layers[layers.size() - 1].layer_errors[0] << "|\n" << std::endl;
        std::cout << "Error 2: |" << layers[layers.size() - 1].layer_errors[1] << "|\n" << std::endl;
        std::cout << "Error 3: |" << layers[layers.size() - 1].layer_errors[2] << "|\n" << std::endl;
    }
    
    prev_layer = layers[layers.size() - 1];

    for(int layer = (layers.size() - 2); layer >= 0; layer--) {
        layers[layer].calculateErrorFromNextLayer(prev_layer);
        prev_layer = layers[layer];
    }

    // 3. Backpropagate error through layers
    for(auto& layer : layers) {
        layer.applyErrorsToLayer();
    }

    if(DEBUG_MODE)
        std::cout << std::endl;
}

// SEVERAL METHODS FOR TRAINING OVERLOADING
void Model::train_model(const List& data, const List& answers) {
    train(data, answers);
}

void Model::train_model(const std::vector<float>& data, const std::vector<float>& answers) {
    train(data, answers);
}

void Model::train_model(const List& data, const List& answers, int iterations) {
    // Perform training
    for(int i = 0; i < iterations; i++)
    {
        if(DEBUG_MODE)
            printf("\n\n=====TRAINING MODEL=====\n\n");

        if(i % (iterations / 100) == 0)
            std::cout << "Training " << ( (float)i / (float)iterations ) * 100 << "% complete..." << std::endl;

        train(data, answers);
    }
    std::cout << std::endl;
}

void Model::train_model(const std::vector<float>& data, const std::vector<float>& answers, int iterations) {
    // Perform training
    for(int i = 0; i < iterations; i++)
    {
        if(DEBUG_MODE)
            printf("\n\n=====TRAINING MODEL=====\n\n");

        if(i % (iterations / 100) == 0)
            std::cout << "Training " << ( (float)i / (float)iterations ) * 100 << "% complete..." << std::endl;

        train(data, answers);
    }
    std::cout << std::endl;
}

void Model::train_model(std::vector<std::vector<float>> data, std::vector<std::vector<float>> answers, int iterations, int sampleStep) {
    // Modify input and answers using sampleStep
    Matrix sampledData;
    Matrix sampledAnswers;

    for(int index = 0; index < data.size(); index += sampleStep) {
        sampledData.emplace_back(data[index]);
        sampledAnswers.emplace_back(answers[index]);
    }

    // Perform training
    for(int i = 0; i < iterations; i++)
    {
        if(DEBUG_MODE)
            printf("\n\n=====TRAINING MODEL=====\n\n");

        if(i % (iterations / 100) == 0)
            std::cout << "Training " << ( (float)i / (float)iterations ) * 100 << "% complete..." << std::endl;

        for(int x = 0; x < sampledData.size(); x++) {
            train(sampledData[x], sampledAnswers[x]);
        }
    }
    std::cout << std::endl;
}

void Model::train_model(Matrix& data, Matrix& answers, int iterations, int sampleStep) {
    // Modify input and answers using sampleStep
    Matrix sampledData;
    Matrix sampledAnswers;

    for(int index = 0; index < data.size(); index += sampleStep) {
        sampledData.emplace_back(data[index]);
        sampledAnswers.emplace_back(answers[index]);
    }

    // Perform training
    for(int i = 0; i < iterations; i++)
    {
        if(DEBUG_MODE)
            printf("\n\n=====TRAINING MODEL=====\n\n");

        if(i % (iterations / 100) == 0)
            std::cout << "Training " << ( (float)i / (float)iterations ) * 100 << "% complete..." << std::endl;

        for(int x = 0; x < sampledData.size(); x++) {
            train(sampledData[x], sampledAnswers[x]);
        }
    }

    std::cout << std::endl;
}
// END OF TRAINING METHODS

void Model::printLayer(Layer& layer) {
    for(float output : layer.layer_outputs) {
        std::cout << output << " ";
    }
    std::cout << std::endl;
}

void Model::run_model(const std::vector<float>& data) {
	std::cout << "========RUNNING MODEL========" << std::endl;
	std::cout << "Inputs: ";
	for(float value : data) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	// Run input layer with data
	layers[0].runLayerWithInput(data);
	Layer prev_layer = layers[0];

	// Run other layers
	for(int layer = 1; layer < layers.size(); layer++) {
		layers[layer].runLayerWithLayer(prev_layer);
        prev_layer = layers[layer];
	}

	// Print output
    std::cout << "Model Output: ";
    printLayer(layers[layers.size() - 1]);

	std::cout << std::endl;
}

void Model::run_model(const std::vector<std::vector<float>>& data, int sampleStep) {
    // Modify input and answers using sampleStep
    Matrix sampledData;

    for(int index = 0; index < data.size(); index += sampleStep) {
        sampledData.emplace_back(data[index]);
    }

    for(auto & t_case : sampledData) {
        std::cout << "========RUNNING MODEL========" << std::endl;
        std::cout << "Inputs: ";

        for (float value: t_case) {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        // Run input layer with data
        layers[0].runLayerWithInput(t_case);
        Layer prev_layer = layers[0];

        // Run other layers
        for (int layer = 1; layer < layers.size(); layer++) {
            layers[layer].runLayerWithLayer(prev_layer);
            prev_layer = layers[layer];
        }

        // Print output
        std::cout << "Model Output: ";
        printLayer(layers[layers.size() - 1]);

        std::cout << std::endl;
    }
}

void Model::run_model(Matrix data, int sampleStep) {
    // Modify input and answers using sampleStep
    Matrix sampledData;

    for(int index = 0; index < data.size(); index += sampleStep) {
        sampledData.emplace_back(data[index]);
    }

    for(int t = 0; t < sampledData.size(); t++) {
        std::cout << "========RUNNING MODEL========" << std::endl;
        std::cout << "Inputs: ";

        for (float value: sampledData[t]) {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        // Run input layer with data
        layers[0].runLayerWithInput(sampledData[t]);
        Layer prev_layer = layers[0];

        // Run other layers
        for (int layer = 1; layer < layers.size(); layer++) {
            layers[layer].runLayerWithLayer(prev_layer);
            prev_layer = layers[layer];
        }

        // Print output
        std::cout << "Model Output: ";
        printLayer(layers[layers.size() - 1]);

        std::cout << std::endl;
    }
}
