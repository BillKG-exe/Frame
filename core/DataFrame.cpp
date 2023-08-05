#include "DataFrame.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <unordered_map>


DataFrame::DataFrame() { }

/* //Adds a column to the data frame
void DataFrame::addColumn(const std::string& colName) {
    columns[colName] = {};
    col_index.addLabel(colName, columns.size()-1);
}
 */
//Adds a column to the data frame
void DataFrame::addColumn(const std::string& colName, const Series& series) {
    columns[colName] = series;
    col_index.addLabel(colName, columns.size()-1);
}

//Drops a column from the data frame
void DataFrame::dropColumn(const std::string& colName) {
    auto it = columns.find(colName);

    if(it != columns.end()) {
        columns.erase(colName);
        col_index.removeLabel(colName);
    }
    throw std::runtime_error("Column name not found");
}

//Adds a new row to the data frame 
void DataFrame::addRow(size_t row, std::vector<double> vals) {
    if(vals.size() != columns.size()) {
        std::cout << "Size of row values do not match DataFrame column size\n";
        exit(1);
    }

    std::vector<double> temp(vals.size(), 0);

    for(auto it = columns.begin(); it != columns.end(); it++) {
        it->second.append(vals[col_index.getPosition(it->first)]);
    }
} 

// Set index for data frame
void DataFrame::setIndex(const Index& index) {
    this->index = index;
}

Index DataFrame::getIndex(const Index& index) {
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
    //Logic for getting row values
    //Try to make it more efficent
    //Create vector representing return values
    //Initialize vector with values 0 and columns size
    //for each column name get the index position in col_index
    // set return vector at given position to what the value is in that column
    // at the specified row.

    //Row access o (n) with the number of rows 
}

// Get value at specific location
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

// Set value at given location
void DataFrame::set(int x, int y, double val) {
    if(x > row_size) throw std::out_of_range("row index out of range");
    if(y > columns.size()) throw std::out_of_range("column index out of range");

    for(auto it = columns.begin(); it != columns.end(); it++) {
        if(col_index.getPosition(it->first) == y) {
            it->second.set(x, val);
        }
    }
} 

// Returns columns size 
size_t DataFrame::colSize() {
    return columns.size();
}

// Return row size
size_t DataFrame::rowSize() {
    return row_size;
}

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

// Reads a csv file into a data frame
void DataFrame::read_csv(std::string filepath) {
    //TODO: 
    /* 
        First check if file exist. If not, throw file not found error
        Read first line and convert it into columns names
            for(string s : v) {
                columns[s]; //Will add the string name into the map with Series size 0
            }

        Next read each line and convert it into double vector
        add row to data frame using addRow function from DataFrame
    */
}

// Reads an excel file into a data frame
void DataFrame::read_excel(std::string filepath) {

}

// Reads a file with any extention given a delimiter into a data frame
void DataFrame::read_file(std::string filepath, char delimiter) {

}

void DataFrame::display(int count = 5) {
    if(count > row_size) throw std::runtime_error("count exceeds the row size");

    std::unordered_map<size_t, std::string> cols;

    for(auto it = columns.begin(); it != columns.end(); it++) {
        cols[col_index.getPosition(it->first)] = it->first;
    }

    for(int c = 0; c < columns.size(); c++) {
        std::cout << std::left << std::setw(15) << cols[c] << " ";
    }

    std::cout << std::endl;

    for(int r = 0; r < count; r++) {
        for(int c = 0; c < columns.size(); c++) {
            std::cout << std::left << std::setw(15) << columns[cols[c]].get(r) << " "; 
        }
        std::cout << std::endl;
    }
}