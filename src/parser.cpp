#include "parser.h"
#include <stdexcept>

// === Node Constructors ===

NodeIntLit::NodeIntLit(int v) {
    type = NodeType::IntLit;
    value = v;
}

NodeIdent::NodeIdent(const std::string& n) {
    type = NodeType::Ident;
    name = n;
}

NodeBinExpr::NodeBinExpr(std::string o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
    : op(std::move(o)), lhs(std::move(l)), rhs(std::move(r)) {
    type = NodeType::BinExpr;
}

NodeLet::NodeLet(const std::string& n, std::unique_ptr<Node> e)
    : name(n), expr(std::move(e)) {
    type = NodeType::Let;
}

NodeExit::NodeExit(std::unique_ptr<Node> e)
    : expr(std::move(e)) {
    type = NodeType::Exit;
}

// === Parser Implementation ===

Parser::Parser(const std::vector<Token>& tokens)
    : m_tokens(tokens) {}

std::vector<std::unique_ptr<Node>> Parser::parse_program() {
    std::vector<std::unique_ptr<Node>> stmts;
    while (!match(TokenType::Eof)) {
        if (check(TokenType::Let)) stmts.push_back(parse_let());
        else if (check(TokenType::Exit)) stmts.push_back(parse_exit());
        else throw std::runtime_error("Unexpected token in program");
    }
    return stmts;
}

bool Parser::match(TokenType t) {
    return m_tokens[m_index].type == t;
}

bool Parser::check(TokenType t) {
    return m_tokens[m_index].type == t;
}

Token Parser::consume() {
    return m_tokens[m_index++];
}

std::unique_ptr<Node> Parser::parse_expr() {
    auto lhs = parse_primary();
    while (check(TokenType::Plus) || check(TokenType::Minus) ||
           check(TokenType::Star) || check(TokenType::Slash)) {
        std::string op = consume().value;
        auto rhs = parse_primary();
        lhs = std::make_unique<NodeBinExpr>(op, std::move(lhs), std::move(rhs));
    }
    return lhs;
}

std::unique_ptr<Node> Parser::parse_primary() {
    if (check(TokenType::IntLit))
        return std::make_unique<NodeIntLit>(std::stoi(consume().value));
    if (check(TokenType::Ident))
        return std::make_unique<NodeIdent>(consume().value);
    throw std::runtime_error("Expected primary expression");
}

std::unique_ptr<Node> Parser::parse_let() {
    consume(); // let
    std::string name = consume().value;
    consume(); // =
    auto expr = parse_expr();
    consume(); // ;
    return std::make_unique<NodeLet>(name, std::move(expr));
}

std::unique_ptr<Node> Parser::parse_exit() {
    consume(); // exit
    auto expr = parse_expr();
    consume(); // ;
    return std::make_unique<NodeExit>(std::move(expr));
}
