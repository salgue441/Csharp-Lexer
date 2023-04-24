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
 * @timecomplexity O(n)
 * @spacecomplexity O(1)
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

/**
 * @brief
 * Process the input string in parallel to generate tokens. It is designed
 * to run in a separate thead, tokenizing the input string and storing
 * the token in the shared tokens vector in a thread safe manner.
 * @param input The input string to be tokenized
 * @timecomplexity O(n)
 * @spacecomplexity O(1)
 */
void Lexer::lexer_thread(const std::string_view &input)
{
    std::size_t current_position{0};
    std::optional<std::string_view> token;

    while ((token = get_next_token(input, current_position)))
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_tokens.push_back(std::make_shared<Token>(*token));
        }

        m_cv.notify_one();
    }
}

// Mutator Methods (public)
// Functions (public)
// Functions (private)