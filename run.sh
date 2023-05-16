#!/bin/sh
if [ ! -d "build" ]; then
  mkdir build
fi

# Output directory
if [ ! -d "outputSingle" ]; then
  mkdir outputSingle
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