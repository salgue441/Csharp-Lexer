#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi

# 
cd build
cmake ..

# Running the tests
make run_tests

# Cleanup
make clean
cd ..
