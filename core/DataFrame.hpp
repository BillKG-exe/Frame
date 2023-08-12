#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "series.hpp"
#include "index.hpp"
#include <map>
#include <string>
#include <unordered_map>

class DataFrame {
public: 
    //Constructor
    DataFrame();

    void display(int count = 5, bool text = false);

    //Adds a column to the data frame
/*     void DataFrame::addColumn(const std::string& colName); */

    //Adds a column to the data frame
    void addColumn(const std::string& colName, Series& series);
    
    //Drops a column from the data frame
    void dropColumn(const std::string& colName);

    //Adds a new row to the data frame 
    void addRow(std::vector<double> vals); 

    // This function drops the last row of data frame
    void dropRow();

    // Set index object for data frame
    void setIndex(const Index& index);

    // Get the index object of the data frame
    Index getIndex();

    // Returns a Series representing a column
    Series getColumn(std::string colName);

    // Returns a vector<double> representing a row
    std::vector<double> getRow(size_t row);

    // Get value at specific location
    double get(int x, int y);

    // Set value at given location
    void set(int x, int y, double val); 

    // Returns columns size 
    size_t colSize();

    // Return row size
    size_t rowSize();

    std::vector<double> getFileRow(std::string line, char sep, std::string colName="");

    // Reads a csv file into a data frame
    void read_csv(std::string filepath);

    // Reads an excel file into a data frame
    void read_excel(std::string filepath);

    // Reads a file with any extention given a delimiter into a data frame
    void read_file(std::string filepath, char delimiter);

    //Etablish this function to read RData files
    void read_rdata(std::string filepath);

    /* Next add overload oparator= */
    DataFrame& operator=(DataFrame df2);

    // Add function to numericalize categorical data.
    void to_numeric();

    // Return frequences of categorical values of a columns as well as 
    // their frequences.
    std::map<std::string, int> getFreq(std::string colName);
    
    // Replace categorical values with customs values
    // Should take a dictionary as arguments
    // Could do imputation with mean, mode, median, etc...
    void impute(std::string colName, std::unordered_map<std::string, int>impute_map); 

    void impute(std::string colName, std::string method);

    void eval(std::string expression);

private:
    std::map<std::string, Series> columns;
    std::map<std::string, std::vector<std::string>> raw_cols;
    Index index, col_index;
    int row_size = 0;
};

#endif