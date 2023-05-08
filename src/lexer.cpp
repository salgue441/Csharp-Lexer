/**
 * @file lexer.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the Lexer class
 * @date 2023-05-07
 * @version 0.1
 *
 * @copyright Copyright 2023
 */

#include "lexer.h"

// Methods
/**
 * @brief
 * Gets the tokens from a file
 * @param filename - Name of the file to lex
 * @return std::vector<Token> - Tokens of the file
 */
std::vector<Token> Lexer::get_tokens_from_file(
    const std::string_view &filename)
{
    m_tokens.clear();
    lex_file(filename);

    // Return the tokens
    return m_tokens;
}

// Private (methods)
/**
 * @brief
 * Lex a file and generate the tokens for it
 * @param filename - Name of the file to lex
 */
void Lexer::lex_file(const std::string_view &filename)
{
    std::string current_token;

    for (auto it = filename.begin(); it != filename.end(); ++it)
    {
        // Separator
        if (std::isspace(*it))
        {
            if (!current_token.empty())
            {
                auto token_type = identify_token(current_token);

                m_tokens.emplace_back(current_token, token_type);
                current_token.clear();
            }
        }

        // Operator
        else if (std::find(csharp::m_operators.begin(),
                           csharp::m_operators.end(),
                           current_token + *it) !=
                 csharp::m_operators.end())
        {
            current_token += *it;
            auto token_type = identify_token(current_token);

            m_tokens.emplace_back(current_token, token_type);
            current_token.clear();
        }

        // Comments
        else if (std::find(csharp::m_comments.begin(),
                           csharp::m_comments.end(),
                           current_token + *it) !=
                 csharp::m_comments.end())
        {
            current_token += *it;

            if (current_token == "//")
            {
                while (*it != '\n' && it != filename.end())
                    ++it;

                --it;
            }

            else if (current_token == "/*")
            {
                while (it != filename.end())
                {
                    if (*it == '*' && *(it + 1) == '/')
                    {
                        current_token += "*/";
                        it += 2;

                        break;
                    }
                    else
                        current_token += *it;

                    ++it;
                }

                auto token_type = identify_token(current_token);

                m_tokens.emplace_back(current_token, token_type);
                current_token.clear();
            }
        }

        // Everything else
        else
        {
            current_token += *it;
        }
    }

    // Add the last token
    if (!current_token.empty())
    {
        auto token_type = identify_token(current_token);
        m_tokens.emplace_back(current_token, token_type);
    }
}

/**
 * @brief
 * Identifies the type of a token
 * @param token - Token to identify
 * @return TokenType - Type of the token
 */
TokenType Lexer::identify_token(const std::string_view &token)
{
    if (std::find(csharp::m_keywords.begin(),
                  csharp::m_keywords.end(), token) !=
        csharp::m_keywords.end())
        return TokenType::Keyword;

    if (std::find(csharp::m_literals.begin(),
                  csharp::m_literals.end(), token) !=
        csharp::m_literals.end())
        return TokenType::Literal;

    if (std::find(csharp::m_operators.begin(),
                  csharp::m_operators.end(), token) !=
        csharp::m_operators.end())
        return TokenType::Operator;

    if (std::find(csharp::m_separators.begin(),
                  csharp::m_separators.end(), token) !=
        csharp::m_separators.end())
        return TokenType::Separator;

    if (std::find(csharp::m_comments.begin(),
                  csharp::m_comments.end(), token) !=
        csharp::m_comments.end())
        return TokenType::Comment;

    if (std::find(csharp::m_preprocessor.begin(),
                  csharp::m_preprocessor.end(), token) !=
        csharp::m_preprocessor.end())
        return TokenType::Preprocessor;

    if (std::find(csharp::m_contextual_keywords.begin(),
                  csharp::m_contextual_keywords.end(), token) !=
        csharp::m_contextual_keywords.end())
        return TokenType::ContextualKeyword;

    if (std::find(csharp::m_access_specifiers.begin(),
                  csharp::m_access_specifiers.end(), token) !=
        csharp::m_access_specifiers.end())
        return TokenType::AccessSpecifier;

    if (std::find(csharp::m_attribute_targets.begin(),
                  csharp::m_attribute_targets.end(), token) !=
        csharp::m_attribute_targets.end())
        return TokenType::AttributeTarget;

    if (std::find(csharp::m_attribute_usage.begin(),
                  csharp::m_attribute_usage.end(), token) !=
        csharp::m_attribute_usage.end())
        return TokenType::AttributeUsage;

    if (std::find(csharp::m_escaped_identifiers.begin(),
                  csharp::m_escaped_identifiers.end(), token) !=
        csharp::m_escaped_identifiers.end())
        return TokenType::EscapedIdentifier;

    if (std::find(csharp::m_interpolated_strings.begin(),
                  csharp::m_interpolated_strings.end(), token) !=
        csharp::m_interpolated_strings.end())
        return TokenType::InterpolatedStringLiteral;

    if (std::find(csharp::m_nullables.begin(),
                  csharp::m_nullables.end(), token) !=
        csharp::m_nullables.end())
        return TokenType::NullLiteral;

    if (token[0] == '@')
        return TokenType::VerbatimStringLiteral;

    return TokenType::Identifier;
}
