//
// Created by Kaeden on 1/30/22.
//

#ifndef NEURALNETWORK_DATA_H
#define NEURALNETWORK_DATA_H
#pragma once

class Data
{
private:
	// Sets size limits on data points
	float maxInnerCircle = 0.650;
	float maxOuterCircle = 1.000;

	float minInnerCircle = 0.400;
	float minOuterCircle = 0.750;

public:
	// Generates the two viewable attributes of Data instance
	std::vector<std::vector<float>> data;
	std::vector<std::vector<float>> answers;

private:
	// Generates a Y value for the inner circle based on X
	// Argument is the X value, Y is returned
	float generateYInner(float x);

	// Generates a Y value for the outer circle based on X
	// Argument is the X value, Y is returned
	float generateYOuter(float x);

public:
	// Generates data randomly assigned to either the
	// inner circle or outer circle which is defined above

	// Argument is the number of data points which
	// gets returned as an array of vectors X, Y
	std::vector<std::vector<float>> initializeData(int size);

    // Input is the filepath for the data set
    // output is a pair containing the data and the answers
    // Also sets the data and answers properties in the class
    std::pair<std::vector<std::vector<float>>, std::vector<std::vector<float>>> initializeData(std::string file, int numOfAnswers);
};

#endif //NEURALNETWORK_DATA_H
