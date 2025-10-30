#pragma once
#include <string>
#include <vector>

// === Token Types ===
enum class TokenType { IntLit, Ident, Plus, Minus, Star, Slash, Eq, Semi, Let, Exit, Eof };

// === Token Struct ===
struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

// === Tokenizer ===
class Tokenizer {
public:
    explicit Tokenizer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string m_input;
};
