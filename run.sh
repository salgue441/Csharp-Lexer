if [ ! -d "build" ]; then
  mkdir build
fi

# Configure build with cmake
cd build
cmake ..

# Build the program
make

# Run the program with input and output directories
./Lexer ../input ../output

# Clean up the build files
make clean
cd ..