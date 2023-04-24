/**
 * @file lexer.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief  Lexer class implementation
 * @version 0.1
 * @date 2023-04-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lexer.h"

// Access Methods (Public)
/**
 * @brief
 * Get the html classes
 * @return std::string - Html classes
 */
std::string Lexer::get_html_classes() const
{
    return m_html_classes;
}

/**
 * @brief
 * Get the html title
 * @return std::string - Html title
 */
std::string Lexer::get_html_title() const
{
    return m_html_title;
}

/**
 * @brief
 * Get the tokens
 * @return std::vector<std::shared_ptr<Token>> - Tokens
 */
std::vector<std::shared_ptr<Token>> Lexer::get_tokens() const
{
    return m_tokens;
}

/**
 * @brief
 * Check if the lexer has finished
 * @return true - If the lexer has finished
 * @return false - If the lexer has not finished
 */
bool Lexer::is_finished() const
{
    return m_finished;
}

// Mutator Methods (Public)
/**
 * @brief
 * Set the html classes
 * @param html_classes - Html classes
 */
void Lexer::set_html_classes(const std::string &html_classes)
{
    m_html_classes = html_classes;
}

/**
 * @brief
 * Set the html title
 * @param html_title - Html title
 */
void Lexer::set_html_title(const std::string &html_title)
{
    m_html_title = html_title;
}

/**
 * @brief
 * Set the tokens
 * @param tokens - Tokens
 */
void Lexer::set_tokens(const std::vector<std::shared_ptr<Token>> &tokens)
{
    m_tokens = tokens;
}

// Access Methods (Private)
/**
 * @brief
 * Gets the next token from the input string
 * @param input Input string to be tokenized
 * @param current_position Current position in the input string
 * @return std::optional<std::pair<TokenType, std::string_view>> token
 * @return std::nullopt - If there are no more tokens
 */
std::optional<std::pair<TokenType, std::string_view>> Lexer::get_next_token(
    const std::string_view &input, const std::size_t &current_position) const
{
    std::size_t start_position = input.find_first_not_of(" \t\n\r\f\v",
                                                         current_position);

    if (start_position == std::string_view::npos)
        return std::nullopt;

    std::size_t end_position = input.find_first_of(" \t\n\r\f\v",
                                                   start_position);

    if (end_position == std::string_view::npos)
        end_position = input.size();

    std::string_view token = input.substr(start_position,
                                          end_position - start_position);

    if (is_keyword(token))
        return std::make_pair(TokenType::Keyword, token);
    else if (is_operator(token))
        return std::make_pair(TokenType::Operator, token);
    else if (is_separator(token))
        return std::make_pair(TokenType::Separator, token);
    else if (is_comment(token))
        return std::make_pair(TokenType::Comment, token);
    else if (is_literal(token))
        return std::make_pair(TokenType::Literal, token);
    else
        return std::make_pair(TokenType::Identifier, token);
}
