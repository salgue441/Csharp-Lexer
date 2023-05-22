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

// C++ standard libraries
#include <unordered_map>

// Project files
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

// Operator overloads
/**
 * @brief
 * Operator overload for the equality operator
 * @param other Token to compare
 * @return true If the tokens are equal
 * @return false If the tokens are not equal
 */
bool Token::operator==(const Token &other) const
{
    return m_value == other.m_value && m_type == other.m_type;
}

// Methods (Private)
/**
 * @brief
 * Get the string representation of the token type
 * @param type Type of the token
 * @return std::string String representation of the token type
 */
std::string Token::get_type_string(TokenType type) const
{
    static const std::unordered_map<TokenType, std::string> type_strings = {
        {TokenType::Keyword, "Keyword"},
        {TokenType::Identifier, "Identifier"},
        {TokenType::Literal, "Literal"},
        {TokenType::Operator, "Operator"},
        {TokenType::Separator, "Separator"},
        {TokenType::Comment, "Comment"},
        {TokenType::Preprocessor, "Preprocessor"},
        {TokenType::ContextualKeyword, "ContextualKeyword"},
        {TokenType::AccessSpecifier, "AccessSpecifier"},
        {TokenType::AttributeTarget, "AttributeTarget"},
        {TokenType::AttributeUsage, "AttributeUsage"},
        {TokenType::EscapedIdentifier, "EscapedIdentifier"},
        {TokenType::InterpolatedStringLiteral, "InterpolatedStringLiteral"},
        {TokenType::NullLiteral, "NullLiteral"},
        {TokenType::VerbatimStringLiteral, "VerbatimStringLiteral"},
        {TokenType::RegularExpressionLiteral, "RegularExpressionLiteral"},
        {TokenType::NumericLiteral, "NumericLiteral"},
        {TokenType::Other, "Other"}};

    return type_strings.at(type);
}

// Methods (Public)
/**
 * @brief
 * Get the string representation of the token
 * @return std::string String representation of the token
 */
std::string Token::to_string() const
{
    return "Token: " + m_value + " (" + get_type_string(m_type) + ")";
}
