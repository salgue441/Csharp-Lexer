#!/bin/zsh
if [ ! -d "build" ]; then
  mkdir build
fi

# Configure build with cmake
cd build
cmake ..

# Build the program
make Lexer

# Clean up the build files
make clean
cd ..