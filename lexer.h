/**
 * @file lexer.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Lexer class definition
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
#include <string>
#include <vector>
#include <string_view>
#include <mutex>
#include <condition_variable>
#include <optional>

// Project files
#include "Utils.h"

/**
 * @class Lexer
 * @brief
 * The lexer class is responsible for tokenizing the input file.
 * It uses a thread pool to tokenize the file.
 * The tokens are stored in a vector and can be accessed by the
 * main thread.
 */
class Lexer
{
public: 
    // Constructor
    Lexer() = default;

    // Destructor 
    ~Lexer() = default;

    // Access functions
    std::string get_html_classes() const;
    std::string get_html_title() const;
    std::vector<Token> get_tokens() const;
    bool is_finished() const;

    // Mutator functions
    void set_html_classes(const std::string_view &);
    void set_html_title(const std::string_view &);

    // Public functions
    void tokenize(const std::string_view &);

private:
    std::string m_html_classes;
    std::string m_html_title;
    std::vector<Token> m_tokens;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_finished{false};

    // Private functions
    std::optional<std::string> get_next_token(const std::string_view &);
    void lexer_thread(const std::string_view &, const size_t &, const size_t &);
    void handle_token(const std::string_view &);
};

#endif //! LEXER_H
