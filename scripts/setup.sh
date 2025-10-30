#!/bin/bash
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

rm -rf build
cmake -S . -B build
cmake --build build

# Run your main program
./build/testy

