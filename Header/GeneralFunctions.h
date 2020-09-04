// This header file is a list of general use functions that 
// may be used in the generation of the neural network

// Sets Random seed based on system clock
void setRandomSeed()
{
	time_t currentTime;
	time(&currentTime);

	srand((unsigned int) currentTime);
}

// Finds the max value of a vector of ints
int getMax(std::vector<int> a)
{
	int maxValue = -9999999;
	for(int i = 0; i < a.size(); i++)
	{
		maxValue = fmax(a[i], maxValue);
	}

	return maxValue;
}

// Rotate vector
std::vector<std::vector<float>> transpose(std::vector<std::vector<float>> oldVector)
{
	std::vector<std::vector<float>> newVector;
	for(int x = 0; x < oldVector[0].size(); x++)
	{
		newVector.push_back({});
		for(int i = 0; i < oldVector.size(); i++)
		{
			newVector[x].push_back(oldVector[i][x]);
		}
	}

	return newVector;
}

// Iteration through output float matrix
void printOutputs(std::vector<std::vector<float>> outputs)
{
	for(int x = 0; x < outputs.size(); x++)
	{
		printf("Neuron %i: ", x);
		for(int i = 0; i < outputs[x].size(); i++)
		{
			printf("%f ", outputs[x][i]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Iteration through float vector
void printVector(std::vector<float> vector)
{
	for(int i = 0; i < vector.size(); i++)
	{
		printf("Value %i: %f \n", i, vector[i]);
	}
	std::cout << std::endl;
}
