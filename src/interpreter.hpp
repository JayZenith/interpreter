#pragma once
#include "parser.hpp"
#include <unordered_map>
#include <stdexcept>
#include <iostream>

class Interpreter {
public:
    Interpreter() = default; //default constructor 

    int eval_program(const std::vector<std::unique_ptr<Node>>& stmts) {
        int last = 0;
        for (const auto& stmt : stmts) {
            last = eval_node(stmt.get());
        }
        return last;
    }
    // int eval_program(const std::vector<Node>& stmts) {
    //     int last = 0;
    //     for (const auto& stmt : stmts) {
    //         last = eval_node(stmt);
    //     }
    //     return last;
    // }

private:
    std::unordered_map<std::string, int> env;
    int eval_node(const Node* node) {
        if (auto lit = dynamic_cast<const NodeIntLit*>(node)) return lit->value;
        if (auto ident = dynamic_cast<const NodeIdent*>(node)) {
            auto it = env.find(ident->name);
            if (it == env.end()) throw std::runtime_error("Undefined variable");
            return it->second;
        }
        if (auto bin = dynamic_cast<const NodeBinExpr*>(node)) {
            int lhs = eval_node(bin->lhs.get());
            int rhs = eval_node(bin->rhs.get());
            if (bin->op == "+") return lhs + rhs;
            if (bin->op == "-") return lhs - rhs;
            if (bin->op == "*") return lhs * rhs;
            if (bin->op == "/") return lhs / rhs;
            throw std::runtime_error("Unknown op");
        }
        if (auto let = dynamic_cast<const NodeLet*>(node)) {
            int val = eval_node(let->expr.get());
            env[let->name] = val;
            return val;
        }
        if (auto exit = dynamic_cast<const NodeExit*>(node)) {
            std::exit(eval_node(exit->expr.get()));
        }
        throw std::runtime_error("Unknown node type");
    }


    // int eval_node(const Node& node) {
    //     switch (node.type) {
    //         case NodeType::IntLit:
    //             return node.int_lit.value;
    //         case NodeType::Ident: {
    //             auto it = env.find(node.ident.name);
    //             if (it == env.end()) throw std::runtime_error("Undefined variable: " + node.ident.name);
    //             return it->second;
    //         }
    //         case NodeType::BinExpr: {
    //             int lhs = eval_node(*node.bin_expr.lhs);
    //             int rhs = eval_node(*node.bin_expr.rhs);
    //             if (node.bin_expr.op == "+") return lhs + rhs;
    //             if (node.bin_expr.op == "-") return lhs - rhs;
    //             if (node.bin_expr.op == "*") return lhs * rhs;
    //             if (node.bin_expr.op == "/") return lhs / rhs;
    //             throw std::runtime_error("Unknown binary op: " + node.bin_expr.op);
    //         }
    //         case NodeType::Let: {
    //             int val = eval_node(*node.let_stmt.expr);
    //             env[node.let_stmt.name] = val;
    //             return val; //returns 5 if let x = 5;
    //         }
    //         case NodeType::Exit:
    //             std::exit(eval_node(*node.exit_stmt.expr));
    //     }
    //     throw std::runtime_error("Unknown node type");
    // }
};
