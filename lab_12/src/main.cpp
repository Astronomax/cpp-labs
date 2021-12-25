#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include "matrix.h"

int extract_index(const std::string &s) noexcept {
    try {
        return stoi(s.substr(1, s.size() - 1));
    }
    catch (...) {
        return 0;
    }
}

int main() {
    std::string s;
    std::vector<Matrix> registry(10);
    while (std::cin >> s) {
        try {
            if (s == "load") {
                std::string fname, index;
                std::cin >> index >> fname;
                std::ifstream fin;
                fin.exceptions(std::ifstream::failbit | std::ifstream::eofbit);
                try {
                    fin.open(fname);
                    try {
                        registry.at(extract_index(index)) = load(fin);
                    }
                    catch (std::ifstream::failure &e) {
                        std::cout << "LOAD: invalid file format." << std::endl;
                    }
					fin.close();
                } catch (std::ifstream::failure &e) {
                    std::cout << "LOAD: unable to open file." << std::endl;
                }
            } else if (s == "print") {
                std::string index;
                std::cin >> index;
                std::cout << registry.at(extract_index(index));
            } else if (s == "add") {
                std::string index1, index2;
                std::cin >> index1 >> index2;
                registry.at(extract_index(index1)) += registry.at(extract_index(index2));
            } else if (s == "mul") {
                std::string index1, index2;
                std::cin >> index1 >> index2;
                registry.at(extract_index(index1)) *= registry.at(extract_index(index2));
            } else if (s == "elem") {
                std::string index;
                int row, col;
                std::cin >> index >> row >> col;
                std::cout << registry.at(extract_index(index)).get(row, col) << std::endl;
            } else if (s == "exit")
                break;
        }
        catch (MatrixException &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
