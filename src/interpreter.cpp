#include "interpreter.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib> 

int Interpreter::eval_program(const std::vector<std::unique_ptr<Node>>& stmts) {
    int last = 0;
    for (const auto& stmt : stmts) {
        last = eval_node(stmt.get());
    }
    return last;
}

int Interpreter::eval_node(const Node* node) {
    if (auto lit = dynamic_cast<const NodeIntLit*>(node)) {
        return lit->value;
    }

    if (auto ident = dynamic_cast<const NodeIdent*>(node)) {
        auto it = env.find(ident->name); //if ident was not assigned a value via let we get it == env.end()
        if (it == env.end()) throw std::runtime_error("Undefined variable: " + ident->name);
        return it->second;
    }

    if (auto bin = dynamic_cast<const NodeBinExpr*>(node)) {
        int lhs = eval_node(bin->lhs.get());
        int rhs = eval_node(bin->rhs.get());
        if (bin->op == "+") return lhs + rhs;
        if (bin->op == "-") return lhs - rhs;
        if (bin->op == "*") return lhs * rhs;
        if (bin->op == "/") return lhs / rhs;
        throw std::runtime_error("Unknown binary operator: " + bin->op);
    }

    if (auto let = dynamic_cast<const NodeLet*>(node)) {
        //let x = 5; x -> prints 5
        int val = eval_node(let->expr.get()); //retreive val 5
        env[let->name] = val; //x -> 5
        return val; //return 5
    }

    if (auto exit = dynamic_cast<const NodeExit*>(node)) {
        std::exit(eval_node(exit->expr.get()));
    }

    throw std::runtime_error("Unknown node type encountered");
}
