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
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <optional>
#include <mutex>
#include <condition_variable>

#define MAX_THREADS 8
#define MAX_BUFFER_SIZE 1024

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

    // Access Methods
    std::string get_html_classes() const;
    std::string get_html_title() const;
    std::vector<std::string> get_tokens() const;
    bool get_is_finished() const;

    // Mutator Methods
    void set_html_classes(const std::string &);
    void set_html_title(const std::string &);

    // Public methods
    std::string tokenize(const std::string &);
    void print_tokens() const;
    void print_html() const;

private:
    std::string m_html_classes;
    std::string m_html_title;
    std::vector<std::string> m_tokens;
    std::mutex m_token_mutex;
    std::condition_variable m_token_cv;
    bool is_finished;

    // Private methods
    std::optional<std::string> get_next_token();
    void lexer_thread(const std::string_view &, size_t, size_t);
    void handle_token(const std::string_view &);
};

#endif //! LEXER_H
