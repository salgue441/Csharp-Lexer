#!/bin/bash

if [ ! -d "build" ]; then
  mkdir build
fi

# Change to build directory and run CMake
cd build
cmake ..

# Build and run the tests
make run_tests

# Change back to the parent directory
make clean
cd ..
