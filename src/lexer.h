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

// Standard libraries
#include <thread>
#include <mutex>
#include <string_view>
#include <vector>
#include <string>

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

    // Acess Methods
    std::vector<Token> get_tokens() const;

    // Methods
    void start_lexing(const std::vector<std::string> &);
    void save_to_file(const std::string &, const std::string &);

private:
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::vector<Token> m_tokens;
    std::vector<std::string> m_files;

    // Methods
    void lex(const std::vector<std::string> &);
    void lex_file(const std::string_view &);
    std::vector<Token> tokenize(const std::string_view &);
    TokenType identify_token(const std::string_view &);
    std::string token_to_html(const Token &);
    std::string generate_html(const std::vector<std::string> &);
};

#endif //! LEXER_H