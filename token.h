/**
 * @file token.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Token class definition
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <sstream>
#include <array>
#include <memory>
#include <optional>

// Project files
#include "utils.h"

/**
 * @brief
 * Token types for the lexer
 * @enum TokenType
 */
enum class TokenType
{
    Keyword,
    Identifier,
    Literal,
    Operator,
    Separator,
    Comment,
    Other
};

/**
 * @brief
 * Class for the tokens of the lexer
 * @class Token - type, value
 */
class Token
{
public:
    // Constructor
    Token() = default;
    explicit Token(std::string, TokenType);

    // Destructor
    ~Token() = default;

    // Access methods
    std::string get_value() const;
    TokenType get_type() const;

    // Mutator methods
    void set_value(std::string);
    void set_type(TokenType);

    // Functions
    std::string to_string() const;
    bool is_keyword() const;
    bool is_identifier() const;
    bool is_literal() const;
    bool is_operator() const;
    bool is_separator() const;
    bool is_comment() const;
    bool is_other() const;

private:
    std::string m_value;
    TokenType m_type;

    // Tokens
    static constexpr std::array<const char *, 77> m_keywords = {};
    static constexpr std::array<const char *, 40> m_operators = {};
    static constexpr std::array<const char *, 12> m_separators = {};
    static constexpr std::array<const char *, 4> m_comments = {};
    static constexpr std::array<const char *, 5> m_literals = {};
    static constexpr std::array<const char *, 12> m_preprocessor = {};
    static constexpr std::array<const char *, 3> m_contextual_keywords = {};

    // Advanced tokens
    static constexpr std::array<const char *, 6> m_access_specifiers = {};
    static constexpr std::array<const char *, 4> m_attribute_targets = {};
    static constexpr std::array<const char *, 3> m_attribute_usage = {};
    static constexpr std::array<const char *, 2> m_escaped_identifiers = {};
    static constexpr std::array<const char *, 2> m_interpolated_strings = {};
    static constexpr std::array<const char *, 2> m_nullables = {};
    static constexpr std::array<const char *, 2> m_verbatim_strings = {};
};

#endif //!  TOKEN_H