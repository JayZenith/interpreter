# tunnl - A Tree-Walking Interpreter in C++

A dynamically-typed expression-based language built from scratch in C++. Features a tokenizer, recursive descent parser, and tree-walking interpreter with an interactive REPL.

## Features
* REPL for live code execution
* Arithmetic expressions with operator precedence
* Variable bindings with lexical scoping
* AST-based execution via tree-walk evaluation

### Example
```bash
>>> let x = 10;
10
>>> x * 3 + 2;
32
>>> let y = x - 4;
6
>>> y + x;
16
>>> exit 0;
```

## Architecture 
```bash
src/ # Interpreter source files
├── tokenization.hpp   → Lexer / Tokenizer
├── parser.hpp         → AST + Recursive-Descent Parser
└── interpreter.hpp    → Tree-Walk Evaluator
```

### Pipeline:
1. Tokenizer – Converts source text into tokens (IntLit, Ident, Plus, etc.)
2. Parser – Builds an AST from tokens using recursive descent
3. Interpreter – Evaluates the AST with a dynamic environment map


# Quick Start
### Build
```bash
mkdir build && cd build
cmake .. && make
```
The executable will be `testy` in the `build/` directory.

### Run REPL
```bash
./testy
```


# What I learned 
A langauge runtime that models how real interpreters like Python or Lua execute code, from lexical analysis through syntax tree construction to runtime evaluation.

