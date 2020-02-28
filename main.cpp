#include <array>
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

#include "stringops.h"
#include "prettyprint.h"
#include "YlPrimitives.h"

static std::vector<std::unique_ptr<YlObject>> parse(std::vector<char> input);

static std::vector<std::unique_ptr<YlObject>> g_env;

int main() {
    std::string input;

    while (input != "exit" && input != "quit") {
        std::cout << ">>> ";
        std::getline(std::cin, input);
        std::cout << parse(as_vector(input)).at(0)->to_string() << std::endl;
    }
}

static std::unique_ptr<YlObject> evaluate_statement(const std::vector<char>& st);

static std::unique_ptr<YlObject> parse_integer(const std::vector<char>& st) {
    std::stringstream ss;
    ss << as_string(st);
    int i;
    ss >> i;
    return std::make_unique<YlInteger>(i);
}

static std::unique_ptr<YlObject> parse_bool(const std::vector<char>& st) {
    auto str = trim_copy(as_string(st));
    return str == "true" ? std::make_unique<YlBool>(true) : std::make_unique<YlBool>(false);
}

static std::unique_ptr<YlObject> execute_operator(
    const std::unique_ptr<YlObject>& lhs,
    const std::unique_ptr<YlObject>& rhs,
    const std::string&               op) {
    if (op == "==") {
        return lhs->equals(*rhs)
                   ? std::make_unique<YlBool>(true)
                   : std::make_unique<YlBool>(false);
    } else {
        std::cout << "not implemented: operator " << op << std::endl;
        abort();
    }
}

static std::unique_ptr<YlObject> parse_binary_operator(const std::vector<char>& st, const std::string& op) {
    auto iter    = std::find_first_of(st.begin(), st.end(), op.begin(), op.end());
    auto lhs     = evaluate_statement(std::vector<char>(st.begin(), iter));
    auto rhs_vec = std::vector<char>(iter + op.size(), st.end());
    auto rhs     = evaluate_statement(rhs_vec);
    return execute_operator(lhs, rhs, op);
}

static std::unique_ptr<YlObject> evaluate_statement(const std::vector<char>& st) {
    std::cout << "evaluating \"" << as_string(st) << "\"" << std::endl;
    if (string_is_digits(st)) {
        return parse_integer(st);
    } else if (trim_copy(as_string(st)) == "true" || trim_copy(as_string(st)) == "false") {
        return parse_bool(st);
    } else if (find_string(st, "==") != st.end()) {
        return parse_eqeq(st);
    }
    return std::make_unique<YlNone>();
}

static std::vector<std::unique_ptr<YlObject>> parse(std::vector<char> input) {
    ensure_proper_termination(input);
    std::vector<std::vector<char>> statements;
    std::vector<char>::iterator    iter      = std::find_if(input.begin(), input.end(), is_delimiter);
    std::vector<char>::iterator    last_iter = input.begin();
    while (iter != input.end()) {
        if (iter - last_iter != 0) {
            std::vector<char> new_v(last_iter, iter);
            replace_all(new_v, ";", "");
            replace_all(new_v, "\n", "");
            if (!new_v.empty())
                statements.emplace_back(std::move(new_v));
        }
        last_iter = iter;
        iter      = std::find_if(last_iter + 1, input.end(), is_delimiter);
    }

    std::vector<std::unique_ptr<YlObject>> objects;

    if (statements.empty()) {
        objects.emplace_back(std::make_unique<YlNone>());
        return objects;
    }


    for (const auto& statement : statements) {
        objects.emplace_back(evaluate_statement(statement));
    }

    return objects;
}

