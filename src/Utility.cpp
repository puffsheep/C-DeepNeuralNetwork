#include <time.h>
#include <random>
#include <iostream>

#include "List.h"
#include "Matrix.h"
#include "Utility.h"

// This header file is a list of general use functions that
// may be used in the generation of the neural network

// Sets Random seed based on system clock
void setRandomSeed()
{
	time_t currentTime;
	time(&currentTime);

	srand((unsigned int) currentTime);
}

// Range is the maximum and minimum value
// Resolution is the number of samples possible
float getRandomNumber(int range, int resolution)
{
	float resolutionMultiplier = (1/(float)resolution);
	return ((rand() % (2*range*resolution)) - (range*resolution)) * resolutionMultiplier;
}

// Finds the max value of a vector
float getMax(List array)
{
    float maxValue = array[0];
    for(float index : array)
    {
        maxValue = fmax(index, maxValue);
    }

    return maxValue;
}

float getMax(std::vector<float> array)
{
    float maxValue = array[0];
    for(float index : array)
    {
        maxValue = fmax(index, maxValue);
    }

    return maxValue;
}

// Rotate vector
Matrix transpose(Matrix& oldMatrix)
{
    Matrix newMatrix;
    for(int x = 0; x < oldMatrix[0].size(); x++)
    {
        newMatrix.emplace_back({});
        for(auto & y : oldMatrix)
        {
            newMatrix[x].push_back(y[x]);
        }
    }

    return newMatrix;
}

std::vector<std::vector<float>> transpose(std::vector<std::vector<float>>& oldVector)
{
	std::vector<std::vector<float>> newVector;
	for(int x = 0; x < oldVector[0].size(); x++)
	{
		newVector.emplace_back();
		for(auto & y : oldVector)
		{
			newVector[x].push_back(y[x]);
		}
	}

	return newVector;
}

// Iteration through output float matrix
void printOutputs(std::vector<float>& outputs)
{
	for(int x = 0; x < outputs.size(); x++)
	{
		printf("Neuron %i: ", x);
		printf("%f ", outputs[x]);
	}
	std::cout << std::endl;
}

// Iteration through float vector
void printVector(List& vector)
{
    for(int i = 0; i < vector.size(); i++)
    {
        printf("Value %i: %f \n", i, vector[i]);
    }
    std::cout << std::endl;
}

void printVector(const std::vector<float>& vector)
{
	for(int i = 0; i < vector.size(); i++)
	{
		printf("Value %i: %f \n", i, vector[i]);
	}
	std::cout << std::endl;
}

void printMatrix(const std::vector<std::vector<float>>& matrix) {
	for(auto & x : matrix)
	{
		std::cout << "| ";
		for(float i : x)
		{
			std::cout << i << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}

void printMatrix(Matrix& matrix) {
    for(int x = 0; x < matrix.size(); x++)
    {
        std::cout << "| ";
        for(int i = 0; i < matrix[x].size(); i++)
        {
            std::cout << matrix[x][i] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}