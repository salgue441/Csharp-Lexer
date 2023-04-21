if [ ! -d "build" ]; then
  mkdir build
fi

# Configure build with cmake
cd build
cmake ..

# Build the program
make

# Run the program with input file/directory output file/directory
./Lexer ../input ../output

# Clean up the build files
make clean
cd ..