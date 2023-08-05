#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "series.hpp"
#include "index.hpp"
#include <map>
#include <string>

class DataFrame {
public: 
    //Constructor
    DataFrame();

    void display(int count = 5);

    //Adds a column to the data frame
/*     void DataFrame::addColumn(const std::string& colName); */

    //Adds a column to the data frame
    void addColumn(const std::string& colName, const Series& series);
    
    //Drops a column from the data frame
    void dropColumn(const std::string& colName);

    //Adds a new row to the data frame 
    void addRow(size_t row, std::vector<double> vals); 

    // Set index object for data frame
    void setIndex(const Index& index);

    // Get the index object of the data frame
    Index getIndex(const Index& index);

    // Returns a Series representing a column
    Series getColumn(std::string colName);

    // Get value at specific location
    double get(int x, int y);

    // Set value at given location
    void set(int x, int y, double val); 

    // Returns columns size 
    size_t colSize();

    // Return row size
    size_t rowSize();

    // Reads a csv file into a data frame
    void read_csv(std::string filepath);

    // Reads an excel file into a data frame
    void read_excel(std::string filepath);

    // Reads a file with any extention given a delimiter into a data frame
    void read_file(std::string filepath, char delimiter);

private:
    std::map<std::string, Series> columns;
    Index index, col_index;
    int row_size = 0;
};

#endif