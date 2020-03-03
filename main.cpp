#include <array>
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <unordered_map>
#include <optional>

#include "stringops.h"
#include "prettyprint.h"
#include "YlPrimitives.h"

static std::vector<std::shared_ptr<YlObject>> parse(std::vector<char> input);

class Env
{
public:
    using stack_pair_t   = std::pair<std::string, std::shared_ptr<YlObject>>;
    using stack_vector_t = std::vector<stack_pair_t>;

private:
    stack_vector_t m_stack;

public:
    Env()          = default;
    virtual ~Env() = default;

    inline std::optional<std::shared_ptr<YlObject>> get_by_name(const std::string& _name) {
        std::string name = trim_copy(_name);
        auto        iter = std::find_if(m_stack.rbegin(), m_stack.rend(), [name](const auto& pair) { return pair.first == name; });
        return iter == m_stack.rend() ? std::nullopt : std::optional { iter->second };
    }

    inline void push_to_stack(const std::string& name, std::shared_ptr<YlObject> obj) {
        m_stack.emplace_back(name, obj);
    }
};

static std::shared_ptr<Env> g_env;

int main() {
    g_env = std::make_shared<Env>();
    std::string input;

    while (input != "exit" && input != "quit") {
        std::cout << ">>> ";
        std::getline(std::cin, input);
        std::cout << parse(as_vector(input)).at(0)->to_string() << std::endl;
    }
}

static std::shared_ptr<YlObject> evaluate_statement(const std::vector<char>& st);

static std::shared_ptr<YlObject> parse_integer(const std::vector<char>& st) {
    std::stringstream ss;
    ss << as_string(st);
    int i;
    ss >> i;
    return std::make_shared<YlInteger>(i);
}

static std::shared_ptr<YlObject> parse_bool(const std::vector<char>& st) {
    auto str = trim_copy(as_string(st));
    return str == "true" ? std::make_shared<YlBool>(true) : std::make_shared<YlBool>(false);
}

static std::shared_ptr<YlObject> execute_operator(
    const std::shared_ptr<YlObject>& lhs,
    const std::shared_ptr<YlObject>& rhs,
    const std::string&               op) {
    if (op == "==") {
        return lhs->equals(*rhs)
                   ? std::make_shared<YlBool>(true)
                   : std::make_shared<YlBool>(false);
    } else {
        std::cout << "not implemented: operator " << op << std::endl;
        abort();
    }
}

static std::shared_ptr<YlObject> parse_binary_operator(const std::vector<char>& st, const std::string& op) {
    auto iter    = std::find_first_of(st.begin(), st.end(), op.begin(), op.end());
    auto lhs     = evaluate_statement(std::vector<char>(st.begin(), iter));
    auto rhs_vec = std::vector<char>(iter + op.size(), st.end());
    auto rhs     = evaluate_statement(rhs_vec);
    return execute_operator(lhs, rhs, op);
}

static std::shared_ptr<YlObject> parse_assignment(const std::vector<char>& st) {
    auto        iter    = find_string(st, "=");
    std::string lhs     = trim_copy(std::string(st.begin(), iter));
    auto        rhs_vec = std::vector<char>(iter + 1, st.end());
    auto        rhs     = evaluate_statement(rhs_vec);
    auto        obj     = g_env->get_by_name(lhs);
    if (obj.has_value()) {
        auto o = obj.value();
        std::cout << "not implemented: ASSIGNMENT of existing" << std::endl;
    } else {
        g_env->push_to_stack(lhs, rhs);
    }
    return rhs;
}

static std::shared_ptr<YlObject> evaluate_statement(const std::vector<char>& st) {
    std::cout << "evaluating \"" << as_string(st) << "\"" << std::endl;
    if (string_is_digits(st)) {
        return parse_integer(st);
    } else if (auto o = g_env->get_by_name(as_string(st))) {
        return o.value();
    } else if (trim_copy(as_string(st)) == "true" || trim_copy(as_string(st)) == "false") {
        return parse_bool(st);
    } else if (find_string(st, "==") != st.end()) {
        return parse_binary_operator(st, "==");
    } else if (find_string(st, "=") != st.end()) {
        return parse_assignment(st);
    }
    std::cout << "error" << std::endl;
    return std::make_shared<YlNone>();
}

static std::vector<std::shared_ptr<YlObject>> parse(std::vector<char> input) {
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
                statements.emplace_back(new_v);
        }
        last_iter = iter;
        iter      = std::find_if(last_iter + 1, input.end(), is_delimiter);
    }

    std::vector<std::shared_ptr<YlObject>> objects;

    if (statements.empty()) {
        objects.emplace_back(std::make_shared<YlNone>());
        return objects;
    }


    for (const auto& statement : statements) {
        objects.emplace_back(evaluate_statement(statement));
    }

    return objects;
}

