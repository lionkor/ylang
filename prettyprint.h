#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

template<class ContainerT>
void print_container(const ContainerT& v) {
    if (v.empty()) {
        std::cout << "{}" << std::endl;
    }
    std::cout << "{\n";

    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << std::setw(4) << *i;
        if (i + 1 != v.end()) { // if i is NOT last iter before end
            std::cout << ",\n";
        } else {
            std::cout << "\n";
        }
    }
    std::cout << "}" << std::endl;
}

#endif // PRETTY_PRINT_H
