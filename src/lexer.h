/**
 * @file lexer.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Declaration of the Lexer class
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEXER_H
#define LEXER_H

#include <string>        // For string manipulation
#include <string_view>   // For efficient string comparison
#include <vector>        // For tokens
#include <unordered_set> // For efficient keyword checking
#include <thread>        // For multithreading
#include <mutex>         // For thread synchronization
#include <optional>      // For optional token type

// Project files
#include "token.h"
#include "csharp_language.h"

/**
 * @brief
 * Lexer class
 * @class Lexer
 * @details
 * This class is in charge of reading the source code and generating the tokens
 * that will be used to highlight the code.
 */
class Lexer
{
public:
    // Constructor
    Lexer() = default;

    // Destructor
    ~Lexer() = default;

    // Access methods
    std::vector<Token> get_tokens() const;

    // Methods
    std::vector<Token> get_tokens_from_file(
        const std::string_view &);
    void lex_files(const std::vector<std::string> &);
    std::string generate_html(const std::vector<std::string> &);
    void save_to_file(const std::string &, const std::string &);

private:
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::vector<Token> m_tokens;

    // Methods
    void lex_file(const std::string_view &);
    TokenType identify_token(const std::string_view &);
    std::string token_to_html(const Token &);
};

#endif //! LEXER_H