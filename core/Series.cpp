#include "Series.hpp"
#include <stdexcept>
#include <limits>

// Constructor
Series::Series(const std::string& name) {
    this->name = name;
}

Series::Series(const std::string& name, std::vector<double> vals) {
    this->name = name;
    this->data = vals;

    for(auto i : this->data) {
        if(std::_Is_nan(i)) {
            this->is_missing.push_back(true);
        } else {
            this->is_missing.push_back(false);
        }
    }
}

// Adds element into data 
void Series::append(double val) {
    this->data.push_back(val);
    
    if(!std::_Is_nan(val)) {
        this->is_missing.push_back(false);
    } else {
        this->is_missing.push_back(true);
    }
}

// Set val at given position in data
void Series::set(size_t x, double val) {
    this->data[x] = val;
}

// Get the value at given index
double Series::get(size_t x) {
    if (x < this->data.size()) {
        return this->data[x];
    }
    throw std::out_of_range("Index out of range");
}

// Checks if value is missing from given index
bool Series::isMissing(size_t x) {
    if (x < this->is_missing.size()) {
        return this->is_missing[x];
    }
    throw std::out_of_range("Index out of range");
}

// Remove last element from data
double Series::pop() {
    double val = this->data[this->data.size()-1];
    this->data.pop_back();
    this->is_missing.pop_back();
    return val;
}

// Returns data to user
std::vector<double> Series::toVector() {
    return this->data;
}