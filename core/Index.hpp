#ifndef Index_H
#define Index_H

#include <map>
#include <string>

class Index {
public:
    // Constructor
    Index();

    // Displays labels with their indexes
    void display();

    // Add a label and associate it with a position
    void addLabel(const std::string& label, size_t position);

    //Changes position of a label
    void setLabel(const std::string& label, size_t position);

    // Remove a label from label_to_position
    void removeLabel(const std::string& label);

    // Get the position associated with a label
    size_t getPosition(const std::string& label) const;

    //Returns the size of Index
    size_t size();

    /* Next add overload oparator= */

    // Constants
    static const size_t INVALID_POSITION = static_cast<size_t>(-1);
private:
    std::map<std::string, size_t> label_to_position;
};

#endif