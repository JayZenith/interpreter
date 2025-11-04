#include "tokenization.h"
#include <cctype>   // for isspace, isdigit, isalpha, isalnum
#include <string>

Tokenizer::Tokenizer(const std::string& input)
    : m_input(input) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < m_input.size()) {
        char c = m_input[i];
        // cast expects int in range 0..255 or EOF to avoid UB
        if (isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }

        // handles int lit 
        if (isdigit(static_cast<unsigned char>(c))) {
            size_t start = i;
            while (i < m_input.size() && isdigit(static_cast<unsigned char>(m_input[i]))) //while still a digit
                i++;
            tokens.push_back({TokenType::IntLit, m_input.substr(start, i - start)});
            continue;
        }

        // ident or keyword
        if (isalpha(static_cast<unsigned char>(c))) {
            size_t start = i;
            while (i < m_input.size() && isalnum(static_cast<unsigned char>(m_input[i]))) //while still a letter or digit
                i++;
            std::string word = m_input.substr(start, i - start);
            if (word == "let")
                tokens.push_back({TokenType::Let, word});
            else if (word == "exit")
                tokens.push_back({TokenType::Exit, word});
            else
                tokens.push_back({TokenType::Ident, word});
            continue;
        }

        // not covered by above ops 
        switch (c) {
            case '+': tokens.push_back({TokenType::Plus, "+"}); break;
            case '-': tokens.push_back({TokenType::Minus, "-"}); break;
            case '*': tokens.push_back({TokenType::Star, "*"}); break;
            case '/': tokens.push_back({TokenType::Slash, "/"}); break;
            case '=': tokens.push_back({TokenType::Eq, "="}); break;
            case ';': tokens.push_back({TokenType::Semi, ";"}); break;
            default: break;
        }
        i++;
    }

    tokens.push_back({TokenType::Eof, ""});
    return tokens;
}
