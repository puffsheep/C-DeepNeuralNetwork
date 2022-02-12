//
// Created by Kaeden on 1/30/22.
//
// This header file is a list of general use functions that
// may be used in the generation of the neural network

#ifndef NEURALNETWORK_UTILITY_H
#define NEURALNETWORK_UTILITY_H
#pragma once

#include "Matrix.h"

// Sets Random seed based on system clock
void setRandomSeed();

// Range is the maximum and minimum value
// Resolution is the number of samples possible
float getRandomNumber(int range, int resolution);

// Finds the max value of a vector
// Takes array-like type (List or std::vector)
float getMax(List array);
float getMax(std::vector<float> array);

// Rotate vector
Matrix transpose(Matrix& oldVector);
std::vector<std::vector<float>> transpose(std::vector<std::vector<float>>& oldVector);

// Sum a list of floats
float sum(List& list);

// Iteration through output float matrix
void printOutputs(std::vector<float>& outputs);

// Iteration through float vector
void printVector(List& vector);
void printVector(const std::vector<float>& vector);

void printMatrix(Matrix& matrix);
void printMatrix(const std::vector<std::vector<float>>& matrix);

#endif //NEURALNETWORK_UTILITY_H
