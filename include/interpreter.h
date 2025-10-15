#pragma once
#include "parser.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

class Interpreter {
public:
    Interpreter() = default;

    // Evaluate a program (list of statements)
    int eval_program(const std::vector<std::unique_ptr<Node>>& stmts);

private:
    std::unordered_map<std::string, int> env;

    // Evaluate a single node
    int eval_node(const Node* node);
};
