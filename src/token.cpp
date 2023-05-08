/**
 * @file token.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the Token class
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "token.h"

// Constructor
/**
 * @brief
 * Construct a new Token:: Token object
 * @param value Value of the token
 * @param type Type of the token
 */
Token::Token(std::string value, std::optional<TokenType> type)
{
    m_value = value;
    m_type = type.value_or(TokenType::Other);
}

// Access methods
/**
 * @brief
 * Get the value of the token
 * @return std::string Value of the token
 */
std::string Token::get_value() const
{
    return m_value;
}

/**
 * @brief
 * Get the type of the token
 * @return TokenType Type of the token
 */
TokenType Token::get_type() const
{
    return m_type;
}

// Mutator methods
/**
 * @brief
 * Set the value of the token
 * @param value Value of the token
 */
void Token::set_value(std::string value)
{
    m_value = value;
}

/**
 * @brief
 * Set the type of the token
 * @param type Type of the token
 */
void Token::set_type(TokenType type)
{
    m_type = type;
}

// Private methods
/**
 * @brief
 * Gets the string representation of the token type
 */
std::string Token::get_type_string() const
{
    switch (m_type)
    {
    case TokenType::Keyword:
        return "Keyword";
    case TokenType::Identifier:
        return "Identifier";
    case TokenType::Literal:
        return "Literal";
    case TokenType::Operator:
        return "Operator";
    case TokenType::Separator:
        return "Separator";
    case TokenType::Comment:
        return "Comment";
    case TokenType::VerbatimStringLiteral:
        return "VerbatimStringLiteral";
    case TokenType::InterpolatedStringLiteral:
        return "InterpolatedStringLiteral";
    case TokenType::EscapedIdentifier:
        return "EscapedIdentifier";
    default:
        return "Other";
    }
}

// Public methods
/**
 * @brief
 * Prints the token in a readable format
 * @return std::string String with the token
 */
std::string Token::to_string() const
{
    std::ostringstream oss;

    oss << get_type_string() << ": " << m_value;

    return oss.str();
}

/**
 * @brief
 * Checks if a token is a keyword
 * @return true If the token is a keyword
 * @return false If the token is not a keyword
 */
bool Token::is_keyword() const
{
    return m_type == TokenType::Keyword;
}

/**
 * @brief
 * Checks if a token is an identifier
 * @return true If the token is an identifier
 * @return false If the token is not an identifier
 */
bool Token::is_identifier() const
{
    return m_type == TokenType::Identifier;
}

/**
 * @brief
 * Checks if a token is a literal
 * @return true If the token is a literal
 * @return false If the token is not a literal
 */
bool Token::is_literal() const
{
    return m_type == TokenType::Literal;
}

/**
 * @brief
 * Checks if a token is an operator
 * @return true If the token is an operator
 * @return false If the token is not an operator
 */
bool Token::is_operator() const
{
    return m_type == TokenType::Operator;
}

/**
 * @brief
 * Checks if a token is a separator
 * @return true If the token is a separator
 * @return false If the token is not a separator
 */
bool Token::is_separator() const
{
    return m_type == TokenType::Separator;
}

/**
 * @brief
 * Checks if a token is a comment
 * @return true If the token is a comment
 * @return false If the token is not a comment
 */
bool Token::is_comment() const
{
    return m_type == TokenType::Comment;
}

/**
 * @brief
 * Checks if a token is a preprocessor
 * @return true  If the token is a preprocessor
 * @return false If the token is not a preprocessor
 */
bool Token::is_preprocessor() const
{
    return m_type == TokenType::Preprocessor;
}

/**
 * @brief
 * Checks if the token is a contextual keyword
 * @return true If the token is a contextual keyword
 * @return false If the token is not a contextual keyword
 */
bool Token::is_contextual_keyword() const
{
    return m_type == TokenType::ContextualKeyword;
}

/**
 * @brief
 * Checks if the token is an access specifier
 * @return true If the token is an access specifier
 * @return false If the token is not an access specifier
 */
bool Token::is_access_specifier() const
{
    return m_type == TokenType::AccessSpecifier;
}

/**
 * @brief
 * Checks if a token is an attribute target specifier
 * @return true If the token is an attribute target specifier
 * @return false If the token is not an attribute target specifier
 */
bool Token::is_attribute_target() const
{
    return m_type == TokenType::AttributeTarget;
}

/**
 * @brief
 * Checks if a token is an attribute usage specifier
 * @return true If the token is an attribute usage specifier
 * @return false If the token is not an attribute usage specifier
 */
bool Token::is_attribute_usage() const
{
    return m_type == TokenType::AttributeUsage;
}

/**
 * @brief
 * Checks if the token is an espaced identifier
 * @return true If the token is an escaped identifier
 * @return false If the token is not an escaped identifier
 */
bool Token::is_escaped_identifier() const
{
    return m_type == TokenType::EscapedIdentifier;
}

/**
 * @brief
 * Checks if the token is an interpolated string
 * @return true If the token is an interpolated string
 * @return false If the token is not an interpolated string
 */
bool Token::is_interpolated_string() const
{
    return m_type == TokenType::InterpolatedStringLiteral;
}

/**
 * @brief
 * Checks if the token is nullable
 * @return true If the token is nullable
 * @return false If the token is not nullable
 */
bool Token::is_nullable() const
{
    return m_type == TokenType::NullLiteral;
}

/**
 * @brief
 * Checks if the token is a verbatim string
 * @return true If the token is a verbatim string
 * @return false If the token is not a verbatim string
 */
bool Token::is_verbatim_string() const
{
    return m_type == TokenType::VerbatimStringLiteral;
}