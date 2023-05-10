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

#include <algorithm>
#include "lexer.h"
#include "token.cpp"

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

/**
 * @brief
 * Lex a list of files and generate the tokens for them. Uses
 * multithreading to lex the files in parallel time.
 * @param files Vector of files to lex and generate the tokens for
 * @throw std::exception - If an error occurs while lexing the files
 * @note This method is thread-safe
 */
void Lexer::lex_files(const std::vector<std::string> &files)
{
  try
  {
    // Create the threads
    std::vector<std::thread> threads;
    threads.reserve(files.size());

    for (const auto &file : files)
      threads.emplace_back(&Lexer::lex_file, this, file);

    // Wait for the threads to finish
    for (auto &thread : threads)
      thread.join();
  }
  catch (std::exception &e)
  {
    std::cerr << "Error while lexing files: " << e.what()
              << std::endl;
  }
}

// Private (methods)
/**
 * @brief
 * Lex a file and generate the tokens for it
 * @param filename - Name of the file to lex
 * @throw std::exception - If an error occurs while lexing the file
 */
void Lexer::lex_file(const std::string_view &filename)
{
  try
  {
    std::ifstream file(std::string(filename),
                       std::ios::in | std::ios::binary);

    if (!file)
      throw std::runtime_error("Unable to open the file" +
                               std::string(filename));

    std::ostringstream content_stream;
    content_stream << file.rdbuf();
    file.close();

    std::string content = content_stream.str();
    auto tokens = tokenize(content);

    // Identifying the tokens
    for (auto &token : tokens)
    {
      TokenType token_type = identify_token(token.get_value());
      token.set_type(token_type);
    }

    // Store the tokens
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tokens.insert(m_tokens.end(), tokens.begin(),
                    tokens.end());
  }
  catch (std::exception &e)
  {
    std::cerr << "Error while lexing file " << filename << ": "
              << e.what() << std::endl;
  }
}

/**
 * @brief
 * Tokenize a string
 * @param content - String to tokenize
 * @return std::vector<Token> - Tokens of the string
 */
std::vector<Token> Lexer::tokenize(const std::string_view &content)
{
  std::vector<Token> tokens;
  std::string token;

  for (auto &character : content)
  {
    if (std::isspace(character))
    {
      if (!token.empty())
      {
        tokens.emplace_back(token);
        token.clear();
      }
    }
    else if (std::ispunct(character))
    {
      if (!token.empty() && !std::ispunct(token[0]))
      {
        tokens.emplace_back(token);
        token.clear();
      }

      token += character;

      if (!token.empty())
      {
        tokens.emplace_back(token);
        token.clear();
      }
    }
    else
    {
      token += character;
    }
  }

  return tokens;
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
    return TokenType::NumericLiteral;

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

/**
 * @brief
 * Token to html string
 * @param token - Token to convert
 * @return std::string - Html string
 */
std::string token_to_html(const Token &token)
{
  std::string html = "<span class=\"";
  switch (token.get_type())
  {
  case TokenType::Keyword:
    html += "keyword";
    break;

  case TokenType::Identifier:
    html += "identifier";
    break;

  case TokenType::NumericLiteral:
    html += "literal";
    break;

  case TokenType::Operator:
    html += "operator";
    break;

  case TokenType::Separator:
    html += "separator";
    break;

  case TokenType::Comment:
    html += "comment";
    break;

  case TokenType::Preprocessor:
    html += "preprocessor";
    break;

  case TokenType::ContextualKeyword:
    html += "contextual-keyword";
    break;

  case TokenType::AccessSpecifier:
    html += "access-specifier";
    break;

  case TokenType::AttributeTarget:
    html += "attribute-target";
    break;

  case TokenType::AttributeUsage:
    html += "attribute-usage";
    break;

  case TokenType::EscapedIdentifier:
    html += "escaped-identifier";
    break;

  case TokenType::InterpolatedStringLiteral:
    html += "interpolated-string-literal";
    break;

  case TokenType::NullLiteral:
    html += "null-literal";
    break;

  case TokenType::VerbatimStringLiteral:
    html += "verbatim-string-literal";
    break;

  default:
    html += "other";
    break;
  }

  html += "\">" + token.get_value() + "</span>";
  return html;
}
