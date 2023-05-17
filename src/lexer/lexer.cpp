/**
 * @file lexer.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the Lexer class
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */

// Standard libraries
#include <fstream>
#include <filesystem>
#include <iostream>

// Project files
#include "lexer.h"

// Regex
/**
 * @brief
 * Regex for tokenizing the source code
 */
std::regex Lexer::m_regex_tokenizer(R"(\w+|\s+|\/\/[^\n]*|\/\*[\s\S]*?\*\/|[{}()\[\];,.:?><+\-*/%&=!@#$~,_`\\|\""]|=|\"[^\"]*\")");

// Access Methods
/**
 * @brief
 * Gets the tokens generated by the lexer
 * @return std::vector<Token> Vector of tokens
 */
std::vector<Token> Lexer::get_tokens() const
{
    return m_tokens;
}

// Methods (Public)
/**
 * @brief
 * Starts the lexing of the files
 * @param filenames Vector of filenames
 */
void Lexer::start_single(const std::vector<std::string> &filenames)
{
    try
    {
        for (const auto &filename : filenames)
        {
            auto tokens = lex_file(filename);
            save_single(filename, tokens);
        }
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief
 * Starts the parallel lexer functionality
 * @param filenames Vector of filenames
 */
void Lexer::start_multi(const std::vector<std::string> &filenames)
{
    lex_parallel(filenames);
}

// Methods (Private)
/**
 * @brief
 * Starts the parallel lexing of the files
 * @param filenames Vector of filenames
 */
void Lexer::lex_parallel(const std::vector<std::string> &filenames)
{
    std::vector<std::thread> threads;
    threads.resize(std::thread::hardware_concurrency());

    try
    {
        for (const auto &filename : filenames)
        {
            auto tokens = lex_file(filename);

            std::lock_guard<std::mutex> lock(m_file_mutex);
            threads.emplace_back(std::thread(&Lexer::save_multiple, this,
                                             filename, tokens));
        }

        for (auto &thread : threads)
        {
            if (thread.joinable())
                thread.join();
        }

        threads.clear();
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief
 * Lex a file and generate the tokens for said file
 * @param filename Filename to lex
 * @throw std::runtime_error If the file cannot be opened
 */
std::vector<Token> Lexer::lex_file(const std::string_view &filename)
{
    try
    {
        std::ifstream input_file(filename.data(),
                                 std::ios::in | std::ios::binary);

        if (!input_file)
        {
            throw std::runtime_error("Cannot open file: " +
                                     std::string(filename));
        }

        std::string buffer((std::istreambuf_iterator<char>(input_file)),
                           std::istreambuf_iterator<char>());

        input_file.close();

        if (buffer.empty())
            throw std::runtime_error("File is empty: " + std::string(filename));

        return tokenize(buffer);
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief
 * Tokenizes the source code and generates the html code.
 * Uses regex to identify the m_separator tokens in order to highlight
 * them in the html code.
 * @param buffer Source code to tokenize
 * @return std::vector<Token> Vector of html code
 * @throw std::runtime_error If the file cannot be opened
 */
std::vector<Token> Lexer::tokenize(const std::string_view &buffer)
{
    try
    {
        std::string buffer_str(buffer);

        auto token_begin = std::sregex_token_iterator(
            buffer_str.begin(), buffer_str.end(),
            m_regex_tokenizer);

        const auto token_end = std::sregex_token_iterator();

        std::vector<Token> tokens;

        for (auto it{token_begin}; it != token_end; ++it)
        {
            const std::string token = it->str();

            if (!token.empty())
            {
                TokenType token_type = identify_token(token);
                tokens.emplace_back(token, token_type);
            }
        }

        return tokens;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief
 * Creates the unordered map with the csharp constexpr arrays
 * @return std::unordered_map<std::string, std::string> Unordered map with the csharp constexpr arrays
 */
std::unordered_map<std::string_view, TokenType> Lexer::create_token_map() const
{
    std::unordered_map<std::string_view, TokenType> token_map;

    // Reserve space for the unordered map
    std::size_t size = csharp::m_keywords.size() +
                       csharp::m_operators.size() +
                       csharp::m_separators.size() +
                       csharp::m_comments.size() +
                       csharp::m_literals.size() +
                       csharp::m_preprocessor.size() +
                       csharp::m_contextual_keywords.size() +
                       csharp::m_access_specifiers.size() +
                       csharp::m_attribute_targets.size() +
                       csharp::m_attribute_usage.size() +
                       csharp::m_escaped_identifiers.size() +
                       csharp::m_interpolated_strings.size() +
                       csharp::m_nullables.size() +
                       csharp::m_verbatim_strings.size();

    token_map.reserve(size);

    /**
     * @brief
     * Inserts the elements of a container into the unordered map
     * @param container Container to insert
     * @param type TokenType of the container
     * @return void
     */
    auto insert_range = [&](const auto &container, TokenType type)
    {
        for (const auto &item : container)
            token_map.emplace_hint(token_map.end(),
                                   item, type);
    };

    insert_range(csharp::m_keywords, TokenType::Keyword);
    insert_range(csharp::m_operators, TokenType::Operator);
    insert_range(csharp::m_separators, TokenType::Separator);
    insert_range(csharp::m_comments, TokenType::Comment);
    insert_range(csharp::m_literals, TokenType::Literal);
    insert_range(csharp::m_preprocessor,
                 TokenType::Preprocessor);
    insert_range(csharp::m_contextual_keywords,
                 TokenType::ContextualKeyword);
    insert_range(csharp::m_access_specifiers,
                 TokenType::AccessSpecifier);
    insert_range(csharp::m_attribute_targets,
                 TokenType::AttributeTarget);
    insert_range(csharp::m_attribute_usage,
                 TokenType::AttributeUsage);
    insert_range(csharp::m_escaped_identifiers,
                 TokenType::EscapedIdentifier);
    insert_range(csharp::m_interpolated_strings,
                 TokenType::InterpolatedStringLiteral);
    insert_range(csharp::m_nullables, TokenType::NullLiteral);
    insert_range(csharp::m_verbatim_strings,
                 TokenType::VerbatimStringLiteral);

    return token_map;
}

/**
 * @brief
 * Identify the token type based of the Token class
 * @param token Token to identify
 * @return TokenType Type of the token
 */
TokenType Lexer::identify_token(const std::string_view &token)
{
    static const std::unordered_map<std::string_view, TokenType>
        token_map = create_token_map();
    const auto it = token_map.find(token);

    if (it != token_map.end())
        return it->second;

    return TokenType::Other;
}

/**
 * @brief
 * Utility function used to escape special characters in the html code.
 * @param str String to escape
 * @return std::string Escaped string
 */
std::string Lexer::escape_html(const std::string &input) const
{
    std::stringstream escaped;
    escaped.str(std::string{});
    escaped << std::noskipws;

    for (char c : input)
    {
        switch (c)
        {
        case '&':
            escaped << "&amp;";
            break;
        case '\"':
            escaped << "&quot;";
            break;
        case '\'':
            escaped << "&#39;";
            break;
        case '<':
            escaped << "&lt;";
            break;
        case '>':
            escaped << "&gt;";
            break;
        default:
            escaped << c;
            break;
        }
    }

    return escaped.str();
}

/**
 * @brief
 * Converts the tokens to html code. Uses the style.css defined classes
 * to color the tokens
 * @param tokens Tokens to convert
 * @return std::string Html code
 */
std::string Lexer::token_to_html(const Token &token) const
{
    static const std::unordered_map<TokenType, std::string> html_tags = {
        {TokenType::Keyword, "<span class=\"Keyword\">"},
        {TokenType::Identifier, "<span class=\"Identifier\">"},
        {TokenType::Literal, "<span class=\"Literal\">"},
        {TokenType::Operator, "<span class=\"Operator\">"},
        {TokenType::Separator, "<span class=\"Separator\">"},
        {TokenType::Comment, "<span class=\"Comment\">"},
        {TokenType::Preprocessor, "<span class=\"Preprocessor\">"},
        {TokenType::ContextualKeyword, "<span class=\"ContextualKeyword\">"},
        {TokenType::AccessSpecifier, "<span class=\"AccessSpecifier\">"},
        {TokenType::AttributeTarget, "<span class=\"AttributeTarget\">"},
        {TokenType::AttributeUsage, "<span class=\"AttributeUsage\">"},
        {TokenType::EscapedIdentifier, "<span class=\"EscapedIdentifier\">"},
        {TokenType::InterpolatedStringLiteral,
         "<span class=\"InterpolatedStringLiteral\">"},
        {TokenType::NullLiteral, "<span class=\"NullLiteral\">"},
        {TokenType::VerbatimStringLiteral,
         "<span class=\"VerbatimStringLiteral\">"},
        {TokenType::RegularExpressionLiteral,
         "<span class=\"RegularExpressionLiteral\">"},
        {TokenType::NumericLiteral, "<span class=\"NumericLiteral\">"},
        {TokenType::Other, "<span class=\"Other\">"}};

    std::string html;
    TokenType token_type = token.get_type();

    // Add the html tag
    html += html_tags.at(token_type);

    // Escape the token string
    html += escape_html(token.get_value());

    return html;
}

/**
 * @brief
 * Generates the HTML code from the tokens vector
 * @param tokens Tokens to convert
 * @return std::string Html code
 */
std::string Lexer::generate_html(const std::vector<Token> &tokens) const
{
    std::string html;

    // Reserve space for the html string
    html.reserve(2048);

    // Add the html header
    html += "<!DOCTYPE html>\n"
            "<html lang=\"en\">\n"
            "<head>\n"
            "<meta charset=\"UTF-8\">\n"
            "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            "<title>Highlighter</title>\n"
            "<link rel=\"stylesheet\" href=\"../src/styles/styles.css\">\n"
            "</head>\n"
            "<body style=\"background-color: var(--background-color);\">\n"
            "<pre><code>\n";

    for (const auto &token : tokens)
        html += token_to_html(token);

    html += "</code></pre>\n</body>\n</html>\n";

    return html;
}

/**
 * @brief
 * Gets the output filename from the input filename
 * @param inputFilename Input filename
 * @return std::string Output filename
 */
std::string Lexer::get_output_filename_single(const std::string &inputFilename) const
{
    std::filesystem::path path(inputFilename);
    std::string filename = path.stem().string();

    std::filesystem::path outputPath =
        "../outputSingle/" + filename + ".html";

    return outputPath.string();
}

/**
 * @brief
 * Gets the output filename from the output filename
 * @param inputFilename Input filename
 * @return std::string Output filename
 */
std::string Lexer::get_output_filename_multiple(
    const std::string &inputFilename) const
{
    std::filesystem::path path(inputFilename);
    std::string filename = path.stem().string();

    std::filesystem::path outputPath =
        "../outputParallel/" + filename + ".html";

    return outputPath.string();
}

/**
 * @brief
 * Saves the tokens in a HTML file
 * @param filename Filename to save the tokens
 * @throw std::runtime_error If the file cannot be opened
 */
void Lexer::save_single(const std::string &filename,
                        const std::vector<Token> &tokens) const
{
    try
    {
        std::string output_filename =
            get_output_filename_single(filename);
        std::ofstream output_file(output_filename,
                                  std::ios::out | std::ios::trunc);

        if (!output_file)
            throw std::runtime_error("Cannot open file: " + output_filename);

        output_file << generate_html(tokens);
        output_file.close();
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief
 * Saves the tokens in a HTML file
 * @param filename Filename to save the tokens
 * @throw std::runtime_error If the file cannot be opened
 */
void Lexer::save_multiple(const std::string &filename,
                          const std::vector<Token> &tokens) const
{
    try
    {
        std::string output_filename =
            get_output_filename_multiple(filename);
        std::ofstream output_file(output_filename,
                                  std::ios::out | std::ios::trunc);

        if (!output_file)
            throw std::runtime_error("Cannot open file: " + output_filename);

        output_file << generate_html(tokens);
        output_file.close();
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}