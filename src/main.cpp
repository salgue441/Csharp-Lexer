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
#include <fstream>
#include <memory>
#include <vector>

// Classes
#include "lexer.h"

// Function prototypes
std::vector<std::filesystem::path> get_filenames(const std::string_view &);

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
    if (argc != 2)
    {
        std::cerr
            << "Usage: " << argv[0]
            << " <filename> <output_filename>" << std::endl;

        return 1;
    }

    auto filenames = get_filenames(argv[1]);
    std::cout << "Found " << filenames.size() << " files" << std::endl;
}

// Function definitions
// Auxiliar functions
/**
 * @brief
 * Gets the filename from the arguments passed to the program
 * @param filename - Filename passed to the program
 * @return std::vector<std::filesystem::path> - Vector of filenames
 */
std::vector<std::filesystem::path> get_filenames(
    const std::string_view &input_directory)
{
    std::vector<std::filesystem::path> filenames;
    std::filesystem::path path{input_directory};

    if (!std::filesystem::is_directory(path))
    {
        std::cerr << "Error: " << input_directory
                  << " is not a valid directory" << std::endl;

        exit(1);
    }

    for (const auto &entry : std::filesystem::directory_iterator(path))
        if (entry.path().extension() == ".cs")
            filenames.push_back(entry.path());

    if (filenames.empty())
    {
        std::cerr << "Error: no input files found in "
                  << input_directory << std::endl;

        exit(1);
    }

    return filenames;
}
