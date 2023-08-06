#include "DataFrame.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <unordered_map>
#include <algorithm>


DataFrame::DataFrame() {}

// This function adds a column to the dataframe object
// It also updates the row_size to correspond value of 
// lowest column size
void DataFrame::addColumn(const std::string& colName, Series& series) {
    columns[colName] = series;
    col_index.addLabel(colName, columns.size()-1);

    if(row_size == 0 || series.size() < row_size) {
        row_size = series.size();
    }
}

// This function drops a column belonging to the dataframe object
// Throws a runtime error if the column name provided is not 
// part of the dataframe
void DataFrame::dropColumn(const std::string& colName) {
    auto it = columns.find(colName);
    size_t col_pos = col_index.getPosition(colName);

    if(it != columns.end()) {
        columns.erase(colName);
        col_index.removeLabel(colName);  
    } else throw std::runtime_error("Column name not found");

    for(auto it = columns.begin(); it != columns.end(); it++) {
        size_t pos = col_index.getPosition(it->first);
        if(pos > col_pos) {
            col_index.setLabel(it->first, pos - 1);
        }
    }
}

// This function adds a new row to the data frame 
// and updates the row size. Terminate program if size of
// vector do not match size of dataframe columns
void DataFrame::addRow(std::vector<double> vals) {
    if(vals.size() != columns.size()) {
        std::cout << "Size of row values do not match DataFrame column size\n";
        exit(1);
    }

    for(auto it = columns.begin(); it != columns.end(); it++) {
        it->second.append(vals[col_index.getPosition(it->first)]);
    }
    row_size++;
} 

// This function drops the last row of the data frame
void DataFrame::dropRow() {
    // Removes the last element of each column of the data frame
    for(auto it = columns.begin(); it != columns.end(); it++) {
        if(it->second.size() != 0) it->second.pop();
    }
    row_size--;
}

// Set index for dataframe
void DataFrame::setIndex(const Index& index) {
    this->index = index;
}

// Returns the index of the dataframe
Index DataFrame::getIndex() {
    return index;
}

// Returns a Series representing a column
Series DataFrame::getColumn(std::string colName) {
    auto it = columns.find(colName);

    if(it != columns.end()) {
        return columns[colName];
    }
    throw std::runtime_error("Column name not found");
}

// Returns a vector<double> representing a row
std::vector<double> DataFrame::getRow(size_t row) {
    if(row > row_size) throw std::out_of_range("Row index out of range");

    std::vector<double> hold_vec(columns.size(), 0);

    for(auto it = columns.begin(); it != columns.end(); it++) {
        hold_vec[col_index.getPosition(it->first)] = it->second.get(row);
    }

    return hold_vec;
}

// Get value at specific location in dataframe. EX: dataframe[x][y]
double DataFrame::get(int x, int y) {
    if(x > row_size) throw std::out_of_range("row index out of range");
    if(y > columns.size()) throw std::out_of_range("column index out of range");

    for(auto it = columns.begin(); it != columns.end(); it++) {
        if(col_index.getPosition(it->first) == y) {
            return it->second.get(x);
        }
    }
    return -1;
}

// Set value at given location. EX: dataframe[x][y] = val
void DataFrame::set(int x, int y, double val) {
    if(x > row_size) throw std::out_of_range("row index out of range");
    if(y > columns.size()) throw std::out_of_range("column index out of range");

    for(auto it = columns.begin(); it != columns.end(); it++) {
        if(col_index.getPosition(it->first) == y) {
            it->second.set(x, val);
        }
    }
} 

// Returns columns size of the dataframe
size_t DataFrame::colSize() {
    return columns.size();
}

// Return row size of the dataframe
size_t DataFrame::rowSize() {
    return row_size;
}

// Split a line with gicen separator
std::vector<double> getFileRow(std::string line, char sep) {
    std::vector<double> row;
    std::istringstream iss(line);
    std::string value;

    while (std::getline(iss, value, sep)) {
        try {
            row.push_back(std::stod(value));
        } catch(...) {
            row.push_back(std::numeric_limits<double>::quiet_NaN());
        }
    }
    return row;
}

// Reads a file with any extention given a delimiter into dataframe object
void DataFrame::read_file(std::string filepath, char delimiter) {
    std::ifstream file(filepath);
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        exit(1);
    }

    std::string line;

    std::getline(file, line);
    
    std::istringstream iss(line);
    std::string name;

    // Initializes the data frame column names
    while (std::getline(iss, name, delimiter)) {
        name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char c) {
            return std::isspace(c);
        }), name.end());

        columns[name];
        col_index.addLabel(name, columns.size()-1);
    }

    while(std::getline(file, line)) {
        std::vector<double> row = getFileRow(line, delimiter);
        addRow(row);
    }

    file.close();
}

// Reads a csv file into a data frame
void DataFrame::read_csv(std::string filepath) {
    read_file(filepath, ',');  
}

// Reads an excel file into a data frame
void DataFrame::read_excel(std::string filepath) {
    //To be implemented
}

// Reads an RData file into a data frame
void DataFrame::read_rdata(std::string filepath) {
    //To be implemented
}

// Display the elements of the dataframe in table format
// including column names
void DataFrame::display(int count) {
    if(count > row_size) count = row_size;

    std::unordered_map<size_t, std::string> cols;

    for(auto it = columns.begin(); it != columns.end(); it++) {
        cols[col_index.getPosition(it->first)] = it->first;
    }
    
    for(int c = 0; c < columns.size(); c++) {
        std::cout << std::right << std::setw(15) << cols[c] << " ";
    }

    std::cout << std::endl;

    for(int r = 0; r < count; r++) {
        for(int c = 0; c < columns.size(); c++) {
            std::cout << std::right << std::setw(15) << columns[cols[c]].get(r) << " "; 
        }
        std::cout << std::endl;
    }
}