#include "stringops.h"
#include <algorithm>
#include <iostream>
#include <sstream>

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

bool string_is_digits(const std::vector<char>& st) {
    bool is_digit = true;
    for (auto c : as_string(st)) {
        if (!std::isspace(c) && !std::isdigit(c)) {
            is_digit = false;
            break;
        }
    }
    return is_digit;
}

void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void ltrim(std::vector<char>& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(),
        s.end());
}

void rtrim(std::vector<char>& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(),
        s.end());
}

void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

void trim(std::vector<char>& s) {
    ltrim(s);
    rtrim(s);
}

std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

std::vector<char> ltrim_copy(std::vector<char> s) {
    ltrim(s);
    return s;
}

std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

std::vector<char> rtrim_copy(std::vector<char> s) {
    rtrim(s);
    return s;
}

std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

std::vector<char> trim_copy(std::vector<char> s) {
    trim(s);
    return s;
}

bool string_lexi_equals(const std::vector<char>& st1, const std::vector<char>& st2) {
    auto trimmed_st1 = trim_copy(st1);
    auto trimmed_st2 = trim_copy(st2);
    return std::equal(trimmed_st1.begin(), trimmed_st1.end(), trimmed_st2.begin(), trimmed_st2.end());
}
