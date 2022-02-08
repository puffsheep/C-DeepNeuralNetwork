//
// Created by Kaeden on 1/30/22.
//

#ifndef NEURALNETWORK_LIST_H
#define NEURALNETWORK_LIST_H
#pragma once

class List {
private:
    std::vector<float> list;

public:
    float operator[](int);
    List(std::vector<float>);
    List();

    std::vector<float> toVector();

    void push_back(float val);
    void emplace_back(float val);
    void clear();
    size_t size() const;

    // Iterator functions
    std::vector<float>::iterator begin();
    std::vector<float>::iterator end();

};

#endif //NEURALNETWORK_LIST_H
