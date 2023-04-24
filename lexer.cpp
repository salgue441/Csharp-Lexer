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
/**
 * @brief
 * Gets the html classes string
 * @return std::string The html classes string
 * @timecomplexity O(1) - Because it returns a copy of the string
 * @spacecomplexity O(1) - Because it returns a copy of the string
 */
std::string Lexer::get_html_classes() const
{
    return m_html_classes;
}

/**
 * @brief
 * Gets the html title string
 * @return std::string The html title string
 * @timecomplexity O(1) - Because it returns a copy of the string
 * @spacecomplexity O(1) - Because it returns a copy of the string
 */
std::string Lexer::get_html_title() const
{
    return m_html_title;
}

/**
 * @brief
 * Gets the tokens vector
 * @return std::vector<std::shared_ptr<Token>> The tokens vector
 * @timecomplexity O(1) - Because it returns a copy of the vector
 * @spacecomplexity O(1) - Because it returns a copy of the vector
 */
std::vector<std::shared_ptr<Token>> Lexer::get_tokens() const
{
    return m_tokens;
}

/**
 * @brief
 * Checks if the lexer has finished tokenizing the input string
 * @return true - If the lexer has finished tokenizing the input string
 * @return false - If the lexer has not finished tokenizing the input string
 * @timecomplexity O(1) - Because it returns a boolean
 * @spacecomplexity O(1) - Because it returns a boolean
 */
bool Lexer::is_finished() const
{
    return m_finished;
}

// Access Methods (private)
/**
 * @brief
 * Gets the next token from the input string.
 * @param input The input string to be tokenized
 * @param current_position The current position in the input string
 * @return std::optional<std::string_view> - The next token in the input string
 * @return std::nullopt - If there are no more tokens in the input string
 * @timecomplexity O(m) - Where m is the length of the token
 * @spacecomplexity O(1) - Because it returns a view of the original string
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
/**
 * @brief
 * Sets the html classes string
 * @param html_classes The html classes string
 * @timecomplexity O(1) - Because it sets a string
 * @spacecomplexity O(1) - Because it sets a string
 */
void Lexer::set_html_classes(const std::string &html_classes)
{
    m_html_classes = html_classes;
}

/**
 * @brief
 * Sets the html title string
 * @param html_title The html title string
 * @timecomplexity O(1) - Because it sets a string
 * @spacecomplexity O(1) - Because it sets a string
 */
void Lexer::set_html_title(const std::string &html_title)
{
    m_html_title = html_title;
}

/**
 * @brief
 * Sets the tokens vector to the given vector
 * @param tokens The tokens vector
 * @timecomplexity O(1) - Because it sets a vector
 * @spacecomplexity O(1) - Because it sets a vector
 */
void Lexer::set_tokens(const std::vector<std::shared_ptr<Token>> &tokens)
{
    m_tokens = tokens;
}

// Functions (private)
/**
 * @brief
 * Process the input string in parallel to generate tokens. It is designed
 * to run in a separate thead, tokenizing the input string and storing
 * the token in the shared tokens vector in a thread safe manner.
 * @note Is designed to be run as a separate thread.
 * @param input The input string to be tokenized
 * @timecomplexity O(n) - Where n is the length of the input string
 * @spacecomplexity O(n) - Because the tokens vector is resized
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

/**
 * @brief
 * Handles the token by adding it to the tokens vector. This function is
 * thread safe.
 * @note This function is designed to handle a single token at a time.
 *       It is intended to be used when you already have a token
 *       and you want to add it to the tokens vector.
 * @param token_str The token to be handled
 * @timecomplexity O(1) - Handles a single token at a time
 * @spacecomplexity O(1) - Doesn't allocate any memory on the heap
 */
void Lexer::handle_token(const std::string_view &token_str)
{
    std::shared_ptr<Token> token = std::make_shared<Token>(token_str);

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_tokens.push_back(token);
    }

    m_cv.notify_one();
}

// Functions (public)
/**
 * @brief
 * Divides the input string into chunks and process each chunk in a
 * separate thread. The number of threads is determined based on the
 * available hardware concurrency and the size of the input string.
 * @note This function waits for all the threads to finish before
 * @param input The input string to be tokenized
 * @timecomplexity O(n) - Where n is the length of the input string
 * @spacecomplexity O(t) - Where t is the number of tokens in the input string
 */
void Lexer::tokenize(const std::string_view &input)
{
    std::size_t num_threads{std::min(m_max_threads, input.size())};
    std::size_t chunk_size{input.size() / num_threads};

    for (std::size_t i{}; i < num_threads; ++i)
    {
        std::size_t start_pos{i * chunk_size};
        std::size_t end_pos{i == num_threads - 1
                                ? input.size()
                                : start_pos + chunk_size};

        std::string_view chunk = input.substr(
            start_pos, end_pos - start_pos);

        m_threads.emplace_back(&Lexer::lexer_thread,
                               this, chunk);
    }

    for (auto &thread : m_threads)
        if (thread.joinable())
            thread.join();

    m_finished = true;
}