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
#include <atomic>        // For thread synchronization
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

    // Methods
    void lex_files(const std::vector<std::string> &);

private:
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_is_done;
    std::vector<Token> m_tokens;

    // Methods
    void lex_file(const std::string_view &);
    TokenType identify_token(const std::string_view &);
};

#endif //! LEXER_H