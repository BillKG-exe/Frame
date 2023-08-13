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
std::vector<double> DataFrame::getFileRow(std::string line, char sep, std::string colName) {
    std::vector<double> row;
    std::istringstream iss(line);
    std::string value;

    while (std::getline(iss, value, sep)) {
        try {
            row.push_back(std::stod(value));
        } catch(...) {
            raw_cols[col_index.getLabel(row.size())].push_back(value);
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
        std::vector<double> row = getFileRow(line, delimiter, name);
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
/* NOTE: To display string inside dataset, use a vector of map that has the
        mapping values of categorical columns that will allow manipulation
        of data as number and display of data with their respectives
        categorical string values. Add cat=False into argument to enable
        either display of number or numbers and strings.  
*/
void DataFrame::display(int count, bool text) {
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
            std::cout << std::right << std::setw(15);
            if(text && raw_cols[cols[c]].size() == row_size) {
                std::cout << raw_cols[cols[c]][r] << " ";
            } else {
                std::cout << columns[cols[c]].get(r) << " "; 
            }
        }
        std::cout << std::endl;
    }
}


std::map<std::string, int> DataFrame::getFreq(std::string colName) {
    std::map<std::string, int> freq;

    if(columns.find(colName) == columns.end()) throw std::out_of_range("Column name not found");

    if(raw_cols.find(colName) != raw_cols.end()) {
        for(int i = 0; i < raw_cols[colName].size(); i++) {
            freq[raw_cols[colName][i]]++;
        }
    } else {
        for(int i = 0; i < columns[colName].size(); i++) {
            freq[std::to_string(columns[colName].get(i))]++;
        }
    }

    std::cout << "Format ->  value: freqquency" << std::endl;
    for(auto it = freq.begin(); it != freq.end(); it++) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << std::endl;
}

void DataFrame::impute(std::string colName, std::string method) {
    // Provde code for handling imputation using mean, mode, or median to 
    // replace missing or nan values

    // Check if column is first in raw_cols
    // If yes, handle it based on raw data 
    // Else do it based on the double type values
}

void DataFrame::impute(std::string colName, std::unordered_map<std::string, int> impute_map) {
    if(columns.find(colName) == columns.end()) throw std::out_of_range("Column name not found");

    if(raw_cols[colName].size() != 0) {
        for(int i = 0; i < raw_cols[colName].size(); i++) {
            if(impute_map.find(raw_cols[colName][i]) != impute_map.end()) {
                columns[colName].set(i, impute_map[raw_cols[colName][i]]);
            }
        }
        return;
    }

    for(int i = 0; i < columns[colName].size(); i++) {
        std::string key = std::to_string(int(columns[colName].get(i)));

        if(impute_map.find(key) != impute_map.end()) {
            columns[colName].set(i, impute_map[key]);
        }
    }
}

// Copy data of one dataframe into another
DataFrame& DataFrame::operator=(DataFrame df2) {
    for(auto it = df2.columns.begin(); it != df2.columns.end(); it++) {
        this->columns[it->first] = it->second;
    }

    this->index = df2.index;
    this->col_index = df2.col_index;
    
    return *this;
}

void DataFrame::eval(std::string expression) {

}

void DataFrame::to_numeric() {

}

