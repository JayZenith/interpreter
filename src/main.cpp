#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/tokenization.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

void run_file(const std::string& filename) {
    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Could not open file: " << filename << "\n";
        return;
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string contents = ss.str();

    Tokenizer tokenizer(contents);
    auto tokens = tokenizer.tokenize();

    Parser parser(tokens);
    auto program = parser.parse_program();

    Interpreter interp;
    interp.eval_program(program);
}

void run_repl() {
    Interpreter interp;
    std::string line;
    while (true) {
        std::cout << ">>> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        Tokenizer tokenizer(line);
        auto tokens = tokenizer.tokenize();

        Parser parser(tokens);
        auto program = parser.parse_program();

        try {
            int result = interp.eval_program(program);
            std::cout << result << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Running REPL. Type 'exit <num>;' to quit.\n"; 
        run_repl();
    } else {
        run_file(argv[1]);
    }
    return 0;
}
