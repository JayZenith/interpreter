# tunnl - A Tree-Walking Interpreter in C++

A dynamically-typed expression-based language built from scratch in C++. Features a tokenizer, recursive descent parser, and tree-walking interpreter with an interactive REPL.

## Features
* Interactive REPL for live code execution
* Arithmetic expressions with operator precedence
* Variable bindings with lexical scoping
* AST-based execution via tree-walk evaluation
* Clean pipeline: tokenizer -> parser -> interpreter 

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

### Implementation Highlights
* Recursive descent parsing for expressions and statements
* Dynamic typing with runtime value evaluation
* Environment-based variable resolution using std::unordered_map
* RAII for memory safety with unique_ptr-based AST nodes

# What I learned 
A langauge runtime that models how real interpreters like Python or Lua execute code, from lexical analysis through syntax tree construction to runtime evaluation.


<!-- ## Running the Unit Test
```bash
chmod +x compiler_test.sh
./compiler_test.sh
``` -->
<!-- 
The script: 
1. Creates a sample input file (testInput.txt).
2. Creates the expected assembly output (expectedAssembly.asm).
3. Runs the compiler (./build/testy) on the input file.
4. Compares the generated nasm_out.s against the expected output.
5. Reports success or failure with detailed differences.

## Sample Input (testInput.txt)
```bash
let x = 2 + 3; 
exit x;
```

## Expected Output (expectedAssembly.asm)

```bash
section .data    ; data section
x dq 0           ; global var x (8 bytes) init. to 0

section .text    ; text section
global _start    ; global symbol _start

_start:
    mov rax, 2   ; Load value 2 into register RAX
    mov rbx, rax ; Copy RAX (2)into RBX
    mov rax, 3   ; Overwrite RAX WITH 3 
    add rax, rbx ; Add RBX (2) to RAX (3), Now: RAX = 5
    mov [x], rax ; Store value fo RAX (5), in global var x
    mov rax, [x] ; Load value of x (5) into RAX
    mov rdi, rax ; Copy RAX (5) into RDI vital as Linux sys 
                 ; calls pass 1st arg in RDI
    mov rax, 60  ; Linux x86-64 syscall number 60 = exit
    syscall      ; invoke syscall, termiante with exit code 5


```

## Notes

- The compiler script assumes the executable is named testy and that it - reads test_input.txt and outputs nasm_out.asm.
- You can adjust the paths in compiler_test.sh if your compiler or file names differ.
- Whitespace is normalized for reliable output comparison.
- Designed for a local Linux environment; minor adjustments may be needed for Windows/MacOS.

## x86 Compiler. -->