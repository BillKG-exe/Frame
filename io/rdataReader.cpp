#include <iostream>
#include <fstream>
#include <vector>

struct RDataHeader {
    char marker[4];
    char version[2];
};

int main() {
    std::ifstream file("data.RData", std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    RDataHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(RDataHeader));

    if (std::string(header.marker, 4) != "RDX2" || std::string(header.version, 2) != "03") {
        std::cerr << "Invalid RData file." << std::endl;
        return 1;
    }

    // Read vector data
    std::vector<double> data;
    while (!file.eof()) {
        double value;
        file.read(reinterpret_cast<char*>(&value), sizeof(double));
        data.push_back(value);
    }

    // Print the vector
    for (double value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    file.close();

    return 0;
}
