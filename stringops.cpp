#include "stringops.h"
#include <algorithm>
#include <iostream>

void reduce_spaces(std::string& s) {
    // reduce multiple spaces to one
    auto is_space = [&](std::size_t i) -> bool {
        return s.at(i) == ' ' || s.at(i) == '\t';
    };

    std::string new_s { "" };
    bool        last_was_space { false };
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (is_space(i)) {
            if (last_was_space) {
                continue;
            } else {
                new_s += ' ';
                last_was_space = true;
            }
        } else {
            last_was_space = false;
            new_s += s.at(i);
        }
    }
    s = std::move(new_s);
}

void to_lowercase(std::string& s) {
    std::for_each(s.begin(), s.end(), [](char c) { return std::tolower(c); });
}

std::vector<char> as_vector(const std::string& s) {
    return std::vector<char>(s.begin(), s.end());
}

std::string as_string(const std::vector<char>& v) {
    return std::string(v.data(), v.size());
}

void ensure_proper_termination(std::vector<char>& v) {
    if (v.empty() || !is_delimiter(v.at(v.size() - 1))) {
        v.push_back(';');
    }
}

bool is_delimiter(char c) {
    return c == '\n' || c == ';';
}

void replace_all(std::vector<char>& v, const std::string& repl, const std::string& with) {
    std::vector<char> new_v;
    for (auto it = v.begin(); it != v.end();) {
        if (std::equal(repl.begin(), repl.end(), it)) {
            new_v.insert(new_v.end(), with.begin(), with.end());
            it += repl.end() - repl.begin();
        } else {
            new_v.emplace_back(std::move(*it));
            ++it;
        }
    }
    v = std::move(new_v);
}

void replace_all(std::string& v, const std::string& repl, const std::string& with) {
    // FIXME
}
