#include "Series.hpp"
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>
//#include <iostream>

// Constructor
Series::Series() {}

// Initializes the Series with the column name
Series::Series(const std::string& name) {
    this->name = name;
}

// Initializes the Series with column name as well as its values
Series::Series(const std::string& name, std::vector<double> vals) {
    this->name = name;
    this->data = vals;

    for(auto i : this->data) {
        if(std::isnan(i)) {
            this->is_missing.push_back(true);
        } else {
            this->is_missing.push_back(false);
        }
    }
}

// Adds element into Series data 
void Series::append(double val) {
    this->data.push_back(val);
    
    if(!std::isnan(val)) {
        this->is_missing.push_back(false);
    } else {
        this->is_missing.push_back(true);
    }
}

// Set the name of the serie
void Series::setName(std::string name) {
    this->name = name;
}

// Get the name of the serie
std::string Series::getName() {
    return name;
}

// Set val at given position in sreies' data
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

// Returns the size of the Serie
size_t Series::size() {
    return data.size();
}

// Checks if value is missing from given index
bool Series::isMissing(size_t x) {
    if (x < this->is_missing.size()) {
        return this->is_missing[x];
    }
    throw std::out_of_range("Index out of range");
}

// Remove last element from series' data
double Series::pop() {
    double val = this->data[this->data.size()-1];
    this->data.pop_back();
    this->is_missing.pop_back();
    return val;
}

// Returns series' data to user
std::vector<double> Series::toVector() {
    return this->data;
}

Series& Series::operator=( Series s2) {
    if (this != &s2) { 
        if(name.empty()) {
            name = s2.name;
        }

        if(data.size() == 0) {
            for(int i = 0; i < s2.size(); i++) {
                data.push_back(s2.get(i));
            }
        } else {
            for(int i = 0; i < this->size(); i++) {
                data[i] = this->get(i);
            }
        }
    }
    return *this;
}

/*Series& Series::operator=( Series s2) {
    if (this != &s2) { 
        name = s2.name;
        
        for(int i = 0; i < s2.size(); i++) {
            data.push_back(s2.get(i));
        }
    }
    return *this;
}*/

Series& Series::operator+(Series s2) {
    if (this->size() != s2.size()) throw std::runtime_error("Series are not of same size");
    
    for(int i = 0; i < this->size(); i++) {
        this->data[i] += s2.get(i);
    }

    return *this;
}

Series& Series::operator+(int num) {    
    for(int i = 0; i < this->size(); i++) {
        this->data[i] += double(num);
    }

    return *this;
}

Series& Series::operator+(double num) {
    for(int i = 0; i < this->size(); i++) {
        this->data[i] += num;
    }

    return *this;
}

Series& Series::operator-(Series s2) {
    if (this->size() != s2.size()) throw std::runtime_error("Series are not of same size");
    
    for(int i = 0; i < this->size(); i++) {
        this->data[i] -= s2.get(i);
    }

    return *this;
}

Series& Series::operator-(int num) {
    for(int i = 0; i < this->size(); i++) {
        this->data[i] -= double(num);
    }

    return *this;
}

Series& Series::operator-(double num) {
    for(int i = 0; i < this->size(); i++) {
        this->data[i] -= num;
    }

    return *this;
}

Series& Series::operator*(Series s2) {
    if (this->size() != s2.size()) throw std::runtime_error("Series are not of same size");
    
    for(int i = 0; i < this->size(); i++) {
        this->data[i] *= s2.get(i);
    }

    return *this;
}

Series& Series::operator*(int num) {
    for(int i = 0; i < this->size(); i++) {
        this->data[i] *= double(num);
    }

    return *this;
}

Series& Series::operator*(double num) {
    for(int i = 0; i < this->size(); i++) {
        this->data[i] *= num;
    }

    return *this;
}

Series& Series::operator/(Series s2) {
    if (this->size() != s2.size()) throw std::runtime_error("Series are not of same size");
    
    for(int i = 0; i < this->size(); i++) {
        this->data[i] /= s2.get(i);
    }

    return *this;
}

Series& Series::operator^(int power) {
    for(int i = 0; i < data.size(); i++) {
        data[i] = pow(data[i], power);        
    }

    return *this;
}

void Series::sort() {
    std::sort(data.begin(), data.end());
}