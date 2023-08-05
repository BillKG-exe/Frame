#include "Index.hpp"
#include <stdexcept>

Index::Index() { }

void Index::addLabel(const std::string& label, size_t position) {
    label_to_position[label] = position;
}

void Index::removeLabel(const std::string& label) {
    auto it = label_to_position.find(label);

    if(it != label_to_position.end()) {
        label_to_position.erase(label);
    } else {
        throw std::runtime_error("Label not found");
    }
}

size_t Index::getPosition(const std::string& label) const {
    auto it = label_to_position.find(label);

    if(it != label_to_position.end()) {
        return it->second;
    }

    return INVALID_POSITION;
}