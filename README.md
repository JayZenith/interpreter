# Interpreter

A dynamically-typed expression-based language built in C++. Features a tokenizer, recursive descent parser, and tree-walking interpreter with an interactive REPL.

## Features
* REPL for live code execution
* Arithmetic expressions with operator precedence
* Variable bindings with lexical scoping
* AST-based execution via tree-walk evaluation

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


# What I learned 
A langauge runtime that models how real interpreters like Python or Lua execute code, from lexical analysis through syntax tree construction to runtime evaluation.

