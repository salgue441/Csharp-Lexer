#!/bin/zsh
if [ ! -d "build" ]; then
  mkdir build
fi

# Configure build with cmake
cd build
cmake ..

# Build the program
make run

# Clean up the build files
make clean
cd ..