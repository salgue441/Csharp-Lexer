/**
 * @file lexer.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Lexer class definition
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lexer.h"

// Access Methods
/**
 * @brief
 * Gets the HTML classes for the output file.
 * @return std::string - The HTML classes.
 */
std::string Lexer::get_html_classes() const
{
    return m_html_classes;
}

/**
 * @brief
 * Gets the HTML title for the output file.
 * @return std::string - The HTML title.
 */
std::string Lexer::get_html_title() const
{
    return m_html_title;
}

/**
 * @brief
 * Gets the tokens vector.
 * @return std::vector<Token> - The tokens vector.
 */
std::vector<Token> Lexer::get_tokens() const
{
    return m_tokens;
}

/**
 * @brief
 * Checks if the lexer has finished tokenizing the file.
 * @return true - The lexer has finished tokenizing the file.
 * @return false - The lexer has not finished tokenizing the file.
 */
bool Lexer::is_finished() const
{
    return m_finished;
}

// Mutator Methods
/**
 * @brief
 * Sets the HTML classes for the output file.
 * @param html_classes - The HTML classes.
 */
void Lexer::set_html_classes(const std::string_view &html_classes)
{
    m_html_classes = html_classes;
}

/**
 * @brief
 * Sets the HTML title for the output file.
 * @param html_title - The HTML title.
 */
void Lexer::set_html_title(const std::string_view &html_title)
{
    m_html_title = html_title;
}

// Private Methods
/**
 * @brief
 * Gets the next token from the input file.
 * @param input - The input file.
 * @return std::optional<std::string> - The next token.
 * @return std::nullopt - If there are no more tokens.
 */
std::optional<std::string> Lexer::get_next_token(const std::string_view &input)
{
    static std::size_t pos{};
    static const std::size_t input_size{input.size()};
    static const std::string_view delimeters{" \t\r\n"};

    if (pos == input_size)
        return std::nullopt;

    std::size_t token_start{
        input.find_first_not_of(delimeters, pos)};

    if (token_start == std::string::npos)
        return std::nullopt;

    std::size_t token_end{
        input.find_first_of(delimeters, token_start)};

    if (token_end == std::string::npos)
        token_end = input_size;

    pos = token_end;

    return std::make_shared<std::string>(input.substr(
        token_start, token_end - token_start));
}

/**
 * @brief
 *
 */
void Lexer::lexer_thread(const std::string_view &input)
{
    std::optional<std::string> token{get_next_token(input)};

    while (token)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_tokens.push_back(Token{TokenType::Other, *token});
        lock.unlock();
        m_cv.notify_one();
        token = get_next_token(input);
    }

    m_finished = true;
    m_cv.notify_one();

    return;
}

// Other Methods (public)
/**
 * @brief
 * Tokenizes the input file.
 * @param filenames - The filenames to tokenize.
 * @return void
 * @throw std::runtime_error - If the file cannot be opened.
 */
void Lexer::tokenize(const std::vector<std::string> &filenames)
{
}