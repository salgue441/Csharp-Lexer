/**
 * @file lexer.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Parallel lexer for Csharp language
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEXER_H
#define LEXER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

// Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <optional>

// Constants and macros
#define MAX_THREADS 8
#define MAX_BUFFER_SIZE 1024

// Function prototypes
/**
 * @brief
 * Processes a chunk of input by parsing it and adding the recognized tokens
 * to a shared vector.
 * @param input - The chunk of input to process.
 */
void process_chunks(std::unique_ptr<std::string> &);

/**
 * @brief
 * Starts a pool of workers threads to process the chunks of input.
 * @param chunks - a vector of unique pointers to the chunks of input.
 * @param num_threads - The number of threads to start.
 */
void start_workers(std::vector<std::unique_ptr<std::string>> &, const size_t &);

/**
 * @brief
 * Waits for all the workers to finish processing the chunks of input.
 * @param num_threads - The number of threads to wait for.
 */
void wait_workers(const size_t &);

/**
 * @brief
 * Generates the HTML file with syntax highlighting for the recognized tokens.
 * @param tokens - The vector of recognized tokens.
 * @param filename - The name of the file to generate
 */
void generate_html(const std::vector<std::string> &, const std::string &);

#endif //! LEXER_H