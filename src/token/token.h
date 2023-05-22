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
#include <optional>
#include <ostream>

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

private:
    std::string m_value;
    TokenType m_type;

    // Functions
    std::string get_type_string(TokenType) const;
};

#endif //!  TOKEN_H