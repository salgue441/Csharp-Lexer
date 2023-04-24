/**
 * @file lexer.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Lexer class implementation
 * @version 0.1
 * @date 2023-04-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lexer.h"

// Access Methods (public)
// Access Methods (private)
/**
 * @brief
 * Gets the next token from the input string. This function is thread safe.
 * @param input The input string to be tokenized
 * @param current_position The current position in the input string
 * @return std::optional<std::string_view> - The next token in the input string
 * @return std::nullopt - If there are no more tokens in the input string
 */
std::optional<std::string_view> Lexer::get_next_token(
    const std::string_view &input, std::size_t &current_position) const
{
    current_position = input.find_first_not_of(" \t\n\r\f\v",
                                               current_position);

    if (current_position == std::string_view::npos)
        return std::nullopt;

    std::size_t start_position = current_position;
    current_position = input.find_first_of(" \t\n\r\f\v",
                                           start_position);

    return input.substr(start_position,
                        current_position - start_position);
}

// Mutator Methods (public)
// Functions (public)
// Functions (private)