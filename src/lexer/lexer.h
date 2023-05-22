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
#include <string_view>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>

// Project files
#include "../token/token.h"
#include "../utils/csharp_language.h"

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
    void start_single(const std::vector<std::string> &);
    void start_multi(const std::vector<std::string> &);

private:
    std::vector<Token> m_tokens;
    static std::regex m_regex_tokenizer;

    // Lexer methods
    std::vector<Token> lex_file(const std::string_view &);
    void lex_parallel(const std::vector<std::string> &);
    void lex_and_save(const std::string &);

    // Token methods
    std::vector<Token> tokenize(const std::string_view &);
    std::unordered_map<std::string_view, TokenType> create_token_map() const;
    TokenType identify_token(const std::string_view &);

    // HTML methods
    std::string escape_html(const std::string &) const;
    std::string token_to_html(const Token &) const;
    std::string generate_html(const std::vector<Token> &) const;

    // File methods
    void save_single(const std::string &filename,
                     const std::vector<Token> &) const;
    void save_multiple(const std::string &filename,
                       const std::vector<Token> &) const;
    std::string get_output_filename_single(const std::string &) const;
    std::string get_output_filename_multiple(const std::string &) const;
};

#endif //! LEXER_H