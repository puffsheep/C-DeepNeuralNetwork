//
// Created by Kaeden on 1/30/22.
//
#include <utility>
#include <vector>

#include "Matrix.h"

Matrix::Matrix(std::vector<std::vector<float>> matrix) {
    this->matrix = std::move(matrix);
}

Matrix::Matrix() {
    matrix = {};
}

size_t Matrix::size() const {
    return matrix.size();
}

void Matrix::push_back(const std::vector<float>& list) {
    matrix.push_back(list);
};

void Matrix::emplace_back(const std::vector<float>& list) {
    matrix.emplace_back(list);
};

std::vector<float>& Matrix::operator[](int index) {
    return matrix.at(index);
}

std::vector<std::vector<float>>::iterator Matrix::begin() {
    return matrix.begin();
};

std::vector<std::vector<float>>::iterator Matrix::end() {
    return matrix.end();
};