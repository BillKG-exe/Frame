#include "Index.hpp"
#include <iostream>
#include <stdexcept>

Index::Index() { }

/* 
    Displays the labels as well as positions of each index;
    Format: label -> position
*/
void Index::display() {
    for(auto it = label_to_position.begin(); it != label_to_position.end(); it++) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
}

// Adds a label with given position into the indexes
void Index::addLabel(const std::string& label, size_t position) {
    label_to_position[label] = position;
}

//Changes position of an existing label
void Index::setLabel(const std::string& label, size_t position) {
    label_to_position[label] = position;
}

// Removes a label from the index object
void Index::removeLabel(const std::string& label) {
    auto it = label_to_position.find(label);

    if(it != label_to_position.end()) {
        label_to_position.erase(label);
    } else {
        throw std::runtime_error("Label not found");
    }
}

// Return the position of a label. Position could potentially
// be the row index of accessing data in dataframe object
size_t Index::getPosition(const std::string& label) const {
    auto it = label_to_position.find(label);

    if(it != label_to_position.end()) {
        return it->second;
    }

    return INVALID_POSITION;
}

// Return the size of an index object
size_t Index::size() {
    return label_to_position.size();
}