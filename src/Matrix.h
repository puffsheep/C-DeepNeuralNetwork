//
// Created by Kaeden on 1/30/22.
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H
#pragma once

class Matrix {
private:
    std::vector<std::vector<float>> matrix;

public:
    Matrix(std::vector<std::vector<float>> matrix);
    Matrix();

    size_t size() const;
    void push_back(const std::vector<float>& list);
    void emplace_back(const std::vector<float>& list);

    std::vector<float>& operator[](int index);

    // Iterators
    std::vector<std::vector<float>>::iterator begin();
    std::vector<std::vector<float>>::iterator end();

};

#endif //NEURALNETWORK_MATRIX_H
