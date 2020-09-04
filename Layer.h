class Layer
{
private:
	int layerSize;
	std::vector<std::vector<float>> weights;
	std::vector<float> biases;
	std::vector<Neuron> layer;
	std::vector<std::vector<float>> inputs;

public:
	std::vector<std::vector<float>> unactivated_layer_outputs;
	std::vector<std::vector<float>> layer_outputs;
	std::vector<float> loss{};

public:
	// Initial layer constructor
	Layer(int layerSize, std::vector<std::vector<float>> inputs)
	{
		this->inputs = inputs;
		this->layerSize = layerSize;
		int prevLayerSize = inputs[0].size();

		for(int x = 0; x < layerSize; x++)
		{
			weights.push_back({});
			for(int i = 0; i < prevLayerSize; i++)
			{
				this->weights[x].push_back(((rand() % 2000) - 1000) * 0.0001);
				// printf("%f \n", weights[x][i]);
			}

			this->biases.push_back(0);
			Neuron a(inputs, weights[x], biases[x]);
			layer.push_back(a);
			layer_outputs.push_back(layer[x].output);
			unactivated_layer_outputs.push_back(layer[x].unactivatedOutput);
		}

		printf("Number of neurons in layer: %lu \n", layer_outputs.size());
		printf("Number of batches completed: %lu \n", layer_outputs[0].size());

		printOutputs(layer_outputs);

		layer_outputs = transpose(layer_outputs);
	}

	// Subsequent layer constructor
	Layer(int layerSize, Layer prevLayer)
	{
		this->inputs = prevLayer.layer_outputs;
		this->layerSize = layerSize;
		int prevLayerSize = prevLayer.layerSize;

		for(int x = 0; x < layerSize; x++)
		{
			weights.push_back({});
			for(int i = 0; i < prevLayerSize; i++)
			{
				this->weights[x].push_back(((rand() % 2000) - 1000) * 0.001);
			}

			this->biases.push_back(0);
			Neuron a(inputs, weights[x], biases[x]);
			layer.push_back(a);
			layer_outputs.push_back(layer[x].output);
			unactivated_layer_outputs.push_back(layer[x].unactivatedOutput);
		}

		printf("Number of neurons in layer: %lu \n", layer_outputs.size());
		printf("Number of batches completed: %lu \n", layer_outputs[0].size());

		printOutputs(layer_outputs);

		layer_outputs = transpose(layer_outputs);
	}

	// Mean squared error (MSE) loss function 
	// This function will find the average loss for several batches
	void calculateLoss(std::vector<std::vector<float>> yActual)
	{
		float totalLoss = 0.0;
		for(int x = 0; x < layer_outputs.size(); x++)
		{
			for(int i = 0; i < layer_outputs[x].size(); i++)
			{
				float deltaY = yActual[x][i] - layer_outputs[x][i];
				totalLoss += pow(deltaY, 2);
			}
		}
		totalLoss = totalLoss / (2 * layer_outputs.size());
		loss.push_back(totalLoss);
	}

	// Mean squared error (MSE) loss function 
	// This function will separate each batch into an array
	void calculateLossBySeparateBatch(std::vector<std::vector<float>> yActual)
	{
		for(int x = 0; x < layer_outputs.size(); x++)
		{
			float batchLoss = 0.0;
			for(int i = 0; i < layer_outputs[x].size(); i++)
			{
				float deltaY = yActual[x][i] - layer_outputs[x][i];
				batchLoss += 0.5 * pow(deltaY, 2);
			}
			loss.push_back(batchLoss);
		}
	}

};