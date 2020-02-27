#ifndef STRINGOPS_H
#define STRINGOPS_H

#include <string>
#include <vector>

void              reduce_spaces(std::string&);
void              to_lowercase(std::string&);
std::vector<char> as_vector(const std::string&);
std::string       as_string(const std::vector<char>&);
void              ensure_proper_termination(std::vector<char>&);
bool              is_delimiter(char c);
void              replace_all(std::vector<char>&, const std::string& repl, const std::string& with);
void              replace_all(std::string& v, const std::string& repl, const std::string& with);

#endif // STRINGOPS_H
