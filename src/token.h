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

// C++ standard libraries
#include <string>
#include <sstream>
#include <array>
#include <memory>
#include <optional>

// Project files
#include "csharp_language.h"

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
    Preprocessor,
    ContextualKeyword,
    AccessSpecifier,
    AttributeTarget,
    AttributeUsage,
    EscapedIdentifier,
    InterpolatedStringLiteral,
    NullLiteral,
    VerbatimStringLiteral,
    RegularExpressionLiteral,
    NumericLiteral,
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
    explicit Token(std::string, std::optional<TokenType> = std::nullopt);

    // Destructor
    ~Token() = default;

    // Access methods
    std::string get_value() const;
    TokenType get_type() const;

    // Mutator methods
    void set_value(std::string);
    void set_type(TokenType);

    // Operator overload
    bool operator==(const Token &) const;

    // Functions
    std::string to_string() const;
    bool is_keyword() const;
    bool is_identifier() const;
    bool is_literal() const;
    bool is_operator() const;
    bool is_separator() const;
    bool is_comment() const;
    bool is_preprocessor() const;
    bool is_contextual_keyword() const;
    bool is_access_specifier() const;
    bool is_attribute_target() const;
    bool is_attribute_usage() const;
    bool is_escaped_identifier() const;
    bool is_interpolated_string() const;
    bool is_nullable() const;
    bool is_verbatim_string() const;
    bool is_regular_expression() const;
    bool is_numeric_literal() const;

private:
    std::string m_value;
    TokenType m_type;

    // Functions
    std::string get_type_string() const;
};

#endif //!  TOKEN_H