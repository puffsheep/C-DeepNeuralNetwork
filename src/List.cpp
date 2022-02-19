//
// Created by Kaeden on 1/30/22.
//
#include <utility>
#include <vector>

#include "List.h"

List::List(std::vector<float> vector) {
    list = std::move(vector);
}

List::List() {
    list = {};
}

float& List::operator[](int index) {
    return list.at(index);
}

std::vector<float> List::toVector() {
    return list;
}

std::vector<float>::iterator List::begin() {
    return list.begin();
}

std::vector<float>::iterator List::end() {
    return list.end();
}

size_t List::size() const {
    return list.size();
}

void List::push_back(float val) {
    list.push_back(val);
}

void List::emplace_back(float val) {
    list.emplace_back(val);
}

void List::clear() {
    list.clear();
}
