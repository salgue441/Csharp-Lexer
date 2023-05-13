#!/bin/zsh
if [ ! -d "build" ]; then
  mkdir build
fi

# Output directory
if [ ! -d "output" ]; then
  mkdir output
fi

if [ ! -d "outputParallel" ]; then
  mkdir outputParallel
fi

# Configure build with cmake
cd build
cmake ..

# Build the program
make Lexer

# Clean up the build files
make clean
cd ..