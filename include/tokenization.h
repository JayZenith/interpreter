#pragma once
#include <string>
#include <vector>

enum class TokenType { IntLit, Ident, Plus, Minus, Star, Slash, Eq, Semi, Let, Exit, Eof };

struct Token {
    TokenType type;
    std::string value;
    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

class Tokenizer {
public:
    explicit Tokenizer(const std::string& input); //dont allow implicit conversions
    std::vector<Token> tokenize();

private:
    std::string m_input;
};
