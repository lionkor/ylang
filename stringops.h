#ifndef STRINGOPS_H
#define STRINGOPS_H

#include <algorithm>
#include <string>
#include <vector>

void              reduce_spaces(std::string&);
void              to_lowercase(std::string&);
std::vector<char> as_vector(const std::string&);
std::string       as_string(const std::vector<char>&);
void              ensure_proper_termination(std::vector<char>&);
bool              is_delimiter(char c);
void              replace_all(std::vector<char>&, const std::string& repl, const std::string& with);
bool              string_is_digits(const std::vector<char>& st);
bool              string_is_bool(const std::vector<char>& st);
bool              string_lexi_equals(const std::vector<char>& st1, const std::vector<char>& st2);
void              ltrim(std::string& s);
void              ltrim(std::vector<char>& s);
void              rtrim(std::string& s);
void              rtrim(std::vector<char>& s);
void              trim(std::string& s);
void              trim(std::vector<char>& s);
std::string       ltrim_copy(std::string s);
std::vector<char> ltrim_copy(std::vector<char> s);
std::string       rtrim_copy(std::string s);
std::vector<char> rtrim_copy(std::vector<char> s);
std::string       trim_copy(std::string s);
std::vector<char> trim_copy(std::vector<char> s);

template<class ContainerT>
bool contains(const ContainerT& cont, const std::string& to_find) {
    return std::find_first_of(cont.begin(), cont.end(), to_find.begin(), to_find.end()) != cont.end();
}

template<class ContainerT>
auto find_string(const ContainerT& cont, const std::string& to_find) {
    return std::find_first_of(cont.begin(), cont.end(), to_find.begin(), to_find.end());
}

#endif // STRINGOPS_H

