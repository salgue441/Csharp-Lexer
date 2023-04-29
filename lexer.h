/**
 * @file lexer.h
 * @author Carlos Salguero
 * @brief Declaration of th lexer class
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEXER_H
#define LEXER_H

// C++ standard libraries
#include <string_view>
#include <condition_variable>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <cstdint>
#include <queue>

// Project files
#include "token.h"

/**
 * @brief
 * Class for the lexer in multithreading
 * @class Lexer
 */
class ParallelLexer
{
public:
    // Constructor
    ParallelLexer() = default;

    // Destructor
    ~ParallelLexer() = default;

    // MutatorsJ
    void set_num_threads(const std::uint32_t &);

    // Methods
    void add_input(const std::string_view &);
    void write_token_to_file(const std::string_view &);
    void tokenize();

private:
    std::string m_input{};
    std::uint32_t num_threads{};
    std::vector<std::thread> m_threads{};
    std::vector<std::queue<Token>> m_queues{};
    std::vector<std::mutex> m_mutexes{};
    std::vector<std::condition_variable> m_condition_variables{};
    std::atomic<bool> m_finished{false};

    // Methods
    void tokenize_worker();
    std::vector<std::string> tokenize_chunk(const std::string_view &);
    void split_input_into_chunks();
    void process_token();
};

#endif //! LEXER_H