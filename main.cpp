/**
 * @file main.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Parallel lexer for Csharp language
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <string_view>
#include <filesystem>

// Classes
#include "lexer.h"

// Constants & Macros
#define NUM_THREADS 8

// Function prototypes
std::vector<std::string> get_filename(const std::string_view &filename);
void write_output(const std::string_view &, const std::string_view &);

// Threads structs
struct thread_data
{
};

// Main function
/**
 * @brief
 * Main function of the program
 * @param argc - Number of arguments
 * @param argv - Arguments
 * @return int - 0 if success, 1 if error
 */
int main(int argc, char **argv)
{
    // Check if the number of arguments is correct
    if (argc != 3)
    {
        std::cerr
            << "Usage: " << argv[0]
            << " <filename> <output_filename>" << std::endl;

        return 1;
    }

    std::vector<std::string> filenames = get_filename(argv[1]);

    std::cout
        << "Hello World!" << std::endl;
}

// Function definitions
// Auxiliar functions
/**
 * @brief
 * Gets the filename from the arguments passed to the program
 * @param filename - Filename passed to the program
 * @return std::vector<std::string> - Vector with the filenames
 */
std::vector<std::string> get_filename(const std::string_view &filename)
{
    std::vector<std::string> filenames;

    if (filename.find(".cs") != std::string::npos)
    {
        filenames.reserve(1);
        filenames.push_back(std::string(filename));
    }

    else if (std::filesystem::is_directory(filename))
    {
        for (const auto &entry : std::filesystem::directory_iterator(filename))
            if (entry.path().extension() == ".cs")
                filenames.push_back(entry.path().string());

        filenames.shrink_to_fit();
    }

    else
        throw std::invalid_argument("Invalid filename");

    return filenames;
}

// Threads functions