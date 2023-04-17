/**
 * @file utils.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Auxiliary functions for the lexer
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <optional>

/**
 * @brief
 * Reads a file and returns its contents as a string.
 * @param filename - The name of the file to read.
 * @return std::string - The contents of the file.
 */
std::string read_file(const std::string &);

/**
 * @brief
 * Splits a string into chunks of a given size.
 * @param input - The string to split.
 * @param chunk_size - The size of each chunk.
 * @return std::vector<std::string> - The chunks of the string.
 */
std::vector<std::unique_ptr<std::string>> split_string(
    const std::string &, const size_t &);

#endif //! UTILS_H