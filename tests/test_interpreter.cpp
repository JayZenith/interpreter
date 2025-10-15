#include "interpreter.hpp"
#include "parser.hpp"
#include "tokenization.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <vector>

// Helper to create AST nodes quickly
std::unique_ptr<NodeIntLit> intNode(int val) {
    return std::make_unique<NodeIntLit>(val);
}
std::unique_ptr<NodeIdent> identNode(const std::string& name) {
    return std::make_unique<NodeIdent>(name);
}
std::unique_ptr<NodeBinExpr> binNode(const std::string& op, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs) {
    return std::make_unique<NodeBinExpr>(op, std::move(lhs), std::move(rhs));
}
std::unique_ptr<NodeLet> letNode(const std::string& name, std::unique_ptr<Node> expr) {
    return std::make_unique<NodeLet>(name, std::move(expr));
}
std::unique_ptr<NodeExit> exitNode(std::unique_ptr<Node> expr) {
    return std::make_unique<NodeExit>(std::move(expr));
}

// ==================== Interpreter Tests ====================

TEST(InterpreterTest, IntLiteral) {
    std::vector<std::unique_ptr<Node>> program;
    program.push_back(intNode(42));
    Interpreter interp;
    EXPECT_EQ(interp.eval_program(program), 42);
}

TEST(InterpreterTest, LetStatementAndIdent) {
    std::vector<std::unique_ptr<Node>> program;
    program.push_back(letNode("x", intNode(5)));
    program.push_back(identNode("x"));
    Interpreter interp;
    EXPECT_EQ(interp.eval_program(program), 5);
}

TEST(InterpreterTest, BinaryExpressions) {
    std::vector<std::unique_ptr<Node>> program;

    program.push_back(binNode("+", intNode(3), intNode(2)));
    program.push_back(binNode("-", intNode(10), intNode(4)));
    program.push_back(binNode("*", intNode(2), intNode(3)));
    program.push_back(binNode("/", intNode(8), intNode(2)));

    Interpreter interp;
    EXPECT_EQ(interp.eval_program(program), 4); // last expression 8/2
}

TEST(InterpreterTest, NestedBinaryExpression) {
    auto expr = binNode("*",
                        binNode("+", intNode(1), intNode(2)),
                        binNode("-", intNode(5), intNode(3)));
    std::vector<std::unique_ptr<Node>> program;
    program.push_back(std::move(expr));
    Interpreter interp;
    EXPECT_EQ(interp.eval_program(program), 6); // (1+2)*(5-3)=3*2=6
}

TEST(InterpreterTest, UndefinedVariableThrows) {
    std::vector<std::unique_ptr<Node>> program;
    program.push_back(identNode("y"));
    Interpreter interp;
    EXPECT_THROW(interp.eval_program(program), std::runtime_error);
}

TEST(InterpreterTest, UnknownBinaryOpThrows) {
    std::vector<std::unique_ptr<Node>> program;
    program.push_back(binNode("%", intNode(3), intNode(2)));
    Interpreter interp;
    EXPECT_THROW(interp.eval_program(program), std::runtime_error);
}

TEST(InterpreterTest, ExitNodeExits) {
    std::vector<std::unique_ptr<Node>> program;
    program.push_back(exitNode(intNode(42)));
    Interpreter interp;

    // Expecting std::exit(42), so use EXPECT_DEATH
    EXPECT_DEATH(interp.eval_program(program), ".*");
}

// ==================== Parser + Integration Tests ====================
// Only if parser.hpp/cpp exist

// TEST(ParserTest, ParseIntLiteral) {
//     std::vector<Token> tokens = { Token(TokenType::IntLit, "123"), Token(TokenType::Eof, "") };
//     Parser parser(tokens);
//     auto ast = parser.parse_program();
//     ASSERT_EQ(ast.size(), 1);
//     Interpreter interp;
//     EXPECT_EQ(interp.eval_program(ast), 123);
// }

// TEST(ParserTest, ParseLetStatement) {
//     std::vector<Token> tokens = {
//         Token(TokenType::Let, "let"),
//         Token(TokenType::Ident, "x"),
//         Token(TokenType::Eq, "="),
//         Token(TokenType::IntLit, "7"),
//         Token(TokenType::Semi, ";"),
//         Token(TokenType::Eof, "")
//     };
//     Parser parser(tokens);
//     auto ast = parser.parse_program();
//     ASSERT_EQ(ast.size(), 1);
//     Interpreter interp;
//     EXPECT_EQ(interp.eval_program(ast), 7);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); //Find all TEST() cases and runs them 
    //returns 0 if all pass
}
