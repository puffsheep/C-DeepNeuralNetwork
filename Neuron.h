class Neuron
{
public:
	// Initializes output
	std::vector<float> output;
	std::vector<float> unactivatedOutput;

private:
	// Initializes inputs, weights, and bias of the neuron
	std::vector<std::vector<float>> inputs;
	std::vector<float> weights;
	float bias = 0.0;

private:
	// Note: Rectified Linear Unit (ReLU)
	double ReLU_ActivationFunc(double a)
	{
		return fmax(a, 0);
	}

	// Note: Sigmoid
	double Sigmoid_ActivationFunc(double a)
	{
		return (1 / (1 + exp(a)));
	}

	std::vector<float> getOutput()
	{
		// Initialize the output vector
		std::vector<float> output;

		// Checks if shape is the same
		if(inputs[0].size() == weights.size())
		{
			// Iterates through batch
			for(int x = 0; x < inputs.size(); x++)
			{
				output.push_back(0);

				// Find dot product of inputs & weights
				// (Technically Hadamard product but with each output transposed)
				for(int i = 0; i < inputs[x].size(); i++)
				{
					output[x] += inputs[x][i] * weights[i];
				}
				// Add bias to output
				output[x] += bias;

				unactivatedOutput.push_back(output[x]);

				// MARK: Activation Function Rectified Linear Unit (ReLU)
				output[x] = Sigmoid_ActivationFunc(output[x]);
			}
		}
		else
		{
			printf("Weights size: %lu \n", weights.size());
			printf("Inputs per batch size: %lu \n", inputs[0].size());
			printf("Batch size: %lu \n", inputs.size());
			printf("Error: Inputs and Weights are unequal. \n");
		}	

		return output;
	}

public:
	// Constructor of bias, inputs, weights, and calculating the output
	Neuron(std::vector<std::vector<float>> inputs, std::vector<float> weights, float bias)
	{
		this->bias = bias;
		this->inputs = inputs;
		this->weights = weights;
		this->output = getOutput();
	}

};