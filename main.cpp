#include <array>
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

#include "stringops.h"
#include "prettyprint.h"

static std::optional<std::string> parse(std::vector<char> input);

class YlObject
{
public:
    virtual inline std::size_t id() const { return reinterpret_cast<std::size_t>(this); }
};

int main() {
    std::string input;

    std::string test     = "Green ideas sleep peacefully";
    auto        test_vec = as_vector(test);
    std::cout << as_string(test_vec) << std::endl;
    replace_all(test_vec, "ee", "yoink");
    std::cout << as_string(test_vec) << std::endl;

    return 0;
    while (input != "exit" && input != "quit") {
        std::getline(std::cin, input);
        parse(as_vector(input));
    }
}

static std::optional<std::string> parse(std::vector<char> input) {
    ensure_proper_termination(input);
    std::vector<std::vector<char>> statements;
    std::vector<char>::iterator    iter      = std::find_if(input.begin(), input.end(), is_delimiter);
    std::vector<char>::iterator    last_iter = input.begin();
    while (iter != input.end()) {
        statements.emplace_back(last_iter, iter);
        last_iter = iter;
        iter      = std::find_if(last_iter + 1, input.end(), is_delimiter);
    }

    if (statements.empty()) {
        std::cout << "{}" << std::endl;
    } else {
        std::cout << "{\n";
        for (auto it = statements.begin(); it != statements.end(); ++it) {
            std::cout << "\t" << as_string(*it);
            if (it + 1 != statements.end()) {
                std::cout << ",\n";
            } else {
                std::cout << "\n}" << std::endl;
            }
        }
    }
    return std::nullopt;
}

