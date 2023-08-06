#ifndef SERIES_H
#define SERIES_H

#include <vector>
#include <string>

class Series {
public:
    // Constructor
    Series();

    Series(const std::string& name);

    Series(const std::string& name, std::vector<double> vals);
    
    // Adds element into data 
    void append(double val);

    // Set the name of the serie
    void setName(std::string name);

    // Get the name of the serie
    std::string getName();

    // Set val at given position in data
    void set(size_t x, double val);

    // Get the value at given index
    double get(size_t x);

    // Remove last element from data
    double pop();

    // Returns the size of the Serie
    size_t size();

    // Checks if value is missing from given index
    bool isMissing(size_t x); 

    // Returns vector containing the indices of missing vals
    std::vector<size_t> missings();

    // Returns data to user
    std::vector<double> toVector();

    /* Next Series ops for series as well as int, double and float*/
    /* operator=, *, +, -, / */
    Series& operator=(Series s2);

    Series& operator+(Series s2);
    Series& operator+(int num);
    Series& operator+(double num);

    Series& operator-(Series s2);
    Series& operator-(int num);
    Series& operator-(double num);

    Series& operator*(Series s2);
    Series& operator*(int num);
    Series& operator*(double num);

    Series& operator/(Series s2);


private:
    std::vector<double> data;
    std::vector<bool> is_missing;
    std::string name;
};

#endif