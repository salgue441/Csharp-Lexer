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

// C++ Standard Library
#include <string>
#include <vector>
#include <string_view>        // for std::string_view, std::string_view_literals
#include <mutex>              // for std::mutex, std::lock_guard
#include <condition_variable> // for std::condition_variable
#include <optional>           // for std::optional
#include <pthread.h>          // for pthread_t
#include <future>             // for std::async, std::future
#include <memory>             // for smart pointers

// Project files
#include "Utils.h"

class Lexer
{
public:
    Lexer() = default;
    ~Lexer() = default;

    std::string get_html_classes() const;
    std::string get_html_title() const;
    std::vector<std::unique_ptr<Token>> get_tokens() const;
    bool is_finished() const;

    void set_html_classes(const std::string_view &);
    void set_html_title(const std::string_view &);

    void tokenize(const std::string_view &);

private:
    std::string m_html_classes;
    std::string m_html_title;
    std::vector<std::unique_ptr<Token>> m_tokens;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::size_t m_max_threads{std::thread::hardware_concurrency()};
    bool m_finished{false};
    std::vector<pthread_t> m_threads;
    std::vector<std::future<void>> m_futures;

    std::optional<std::string> get_next_token(const std::string_view &);
    void lexer_thread(const std::string_view &);
    void handle_token(const std::string_view &);
};

#endif // LEXER_H