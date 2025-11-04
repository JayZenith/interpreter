#pragma once
#include "tokenization.h"  // Must define Token and TokenType
#include <string>
#include <vector>
#include <memory>
#include <optional>

// Node Type
enum class NodeType { IntLit, Ident, BinExpr, Let, Exit };

// Base Node
struct Node {
    virtual ~Node() = default; // polymorphic base esp for dynamic cast 
    NodeType type;
};


struct NodeIntLit : Node {
    int value;
    explicit NodeIntLit(int v);
};


struct NodeIdent : Node {
    std::string name;
    explicit NodeIdent(const std::string& n);
};


struct NodeBinExpr : Node {
    std::string op;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;
    NodeBinExpr(const std::string& o, std::unique_ptr<Node> l, std::unique_ptr<Node> r);
};


struct NodeLet : Node {
    std::string name;
    std::unique_ptr<Node> expr;
    NodeLet(const std::string& n, std::unique_ptr<Node> e);
};


struct NodeExit : Node {
    std::unique_ptr<Node> expr;
    explicit NodeExit(std::unique_ptr<Node> e);
};


class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::vector<std::unique_ptr<Node>> parse_program();

private:
    size_t m_index = 0;
    const std::vector<Token>& m_tokens;

    bool match(TokenType t);
    bool check(TokenType t);
    Token consume();

    std::unique_ptr<Node> parse_expr();
    std::unique_ptr<Node> parse_primary();
    std::unique_ptr<Node> parse_let();
    std::unique_ptr<Node> parse_exit();
};
