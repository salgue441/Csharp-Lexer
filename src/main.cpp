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

// C++ standard library
#include <iostream>
#include <string_view>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <memory>

// Classes
#include "lexer/lexer.h"

// Utils
#include "utils/utils.h"

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
            << "input_directory" << std::endl;

        return 1;
    }

    std::string_view input_directory{argv[1]};

    if (!std::filesystem::exists(input_directory) ||
        !std::filesystem::is_directory(input_directory))
    {
        std::cerr << "Error: " << input_directory
                  << " is not a valid directory" << std::endl;
        return 1;
    }

    auto filenames = get_filenames(input_directory);
    std::unique_ptr<Lexer> lexer{std::make_unique<Lexer>()};

    // Convert filenames to strings
    std::vector<std::string> filenames_str;
    std::transform(filenames.begin(), filenames.end(),
                   std::back_inserter(filenames_str),
                   [](const std::filesystem::path &path)
                   {
                       return path.string();
                   });

    // Start the lexer and measure the time
    auto single_time = utils::measure_time([&]()
                                           { lexer->start_single(filenames_str); });

    auto multi_time = utils::measure_time([&]()
                                          { lexer->start_multi(filenames_str); });

    std::cout
        << "Execution time for Single thread Lexer "
        << single_time / 1000.0
        << "s" << std::endl;

    std::cout
        << "Execution time for Multi thread Lexer "
        << multi_time / 1000.0
        << "s" << std::endl;
}

// Function definitions
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
    std::filesystem::path path(input_directory);

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (!std::filesystem::is_regular_file(entry))
            continue;

        if (entry.path().extension() == ".cs")
            filenames.push_back(entry.path());
    }

    if (filenames.empty())
    {
        std::cerr << "Error: no input files found in " << input_directory << std::endl;
        exit(1);
    }

    return filenames;
}
