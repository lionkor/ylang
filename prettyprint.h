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
        return;
    }
    std::cout << "{ ";

    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << std::setw(4) << i->to_string();
        if (i + 1 != v.end()) { // if i is NOT last iter before end
            std::cout << ", ";
        } else {
            std::cout << " }" << std::endl;
        }
    }
}

#endif // PRETTY_PRINT_H
