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
 * @return std::vector<std::string> - The tokens vector.
 */
std::vector<std::string> Lexer::get_tokens() const
{
    return m_tokens;
}

/**
 * @brief
 * Gets the is_finished flag.
 * @return bool - The is_finished flag.
 */
bool Lexer::get_is_finished() const
{
    return is_finished;
}

// Private Access Methods
/**
 * @brief
 * Gets the next token from the buffer and removes it.
 * @return std::optional<std::string> - The next token.
 * @return std::nullopt - If there are no more tokens.
 */
std::optional<std::string> Lexer::get_next_token()
{
    std::unique_lock<std::mutex> lock(m_token_mutex);

    if (m_tokens.empty())
        return std::nullopt;

    std::string token{m_tokens.front()};
    m_tokens.erase(m_tokens.begin());

    return token;
}

// Mutator Methods
/**
 * @brief
 * Sets the HTML classes for the output file.
 * @param html_classes - The HTML classes.
 */
void Lexer::set_html_classes(const std::string &html_classes)
{
    m_html_classes = html_classes;
}

/**
 * @brief
 * Sets the HTML title for the output file.
 * @param html_title - The HTML title.
 */
void Lexer::set_html_title(const std::string &html_title)
{
    m_html_title = html_title;
}

// Private Functions
/**
 * @brief
 * Starts a lexer thread to tokenize a string input. Creates a thread
 * that tokenizes a string input. The input is devided into chunks and
 * each chunk is tokenized by a thread. The tokens are stored in a vector
 * and can be accessed by the main thread.s
 * @param input - The string input to tokenize.
 * @param num_threads - The number of threads to use.
 * @param chunk_size - The size of each chunk.
 * @return std::vector<std::string> - The tokens vector.
 */
void Lexer::lexer_thread(const std::string &input,
                         size_t num_chunks, size_t chunk_size)
{
    std::vector<std::thread> threads;
    std::vector<std::string> chunks;

    size_t input_size{input.size()};

    for (size_t i{}; i < num_chunks; i++)
    {
        size_t start_index{i * chunk_size};
        size_t end_index{(i + 1) * chunk_size};

        if (end_index > input_size)
            end_index = input_size;

        chunks.emplace_back(input.substr(start_index,
                                         end_index - start_index));
    }

    for (size_t i{}; i < num_chunks; i++)
        threads.emplace_back([this, chunk = std::move(chunks[i])]
                             { tokenize(chunk); });

    for (auto &thread : threads)
        thread.join();

    // Signal that tokenization is finished
    {
        std::unique_lock<std::mutex> lock(m_token_mutex);
        is_finished = true;
    }

    m_token_cv.notify_all();
}