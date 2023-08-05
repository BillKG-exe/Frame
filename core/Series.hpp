#ifndef SERIES_H
#define SERIES_H

#include <vector>
#include <string>

class Series {
public:
    // Constructor
    Series(const std::string& name);

    Series(const std::string& name, std::vector<double> vals);
    
    // Adds element into data 
    void append(double val);

    // Set val at given position in data
    void set(size_t x, double val);

    // Get the value at given index
    double get(size_t x);

    // Remove last element from data
    double pop();

    // Checks if value is missing from given index
    bool isMissing(size_t x); 

    // Returns data to user
    std::vector<double> toVector();

private:
    std::vector<double> data;
    std::vector<bool> is_missing;
    std::string name;
};

#endif