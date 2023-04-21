/**
 * @file utils.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Auxiliary functions for the lexer
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

/**
 * @brief
 * Enumeration for the token types
 *
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

struct Token
{
    TokenType type;
    std::string value;
};

#endif //! UTILS_H