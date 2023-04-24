/**
 * @file token.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the Token class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "token.h"

// Array data for the tokens (basic)
/**
 * @brief
 * Array of C# keywords for the lexer
 * @constexpr std::array<const char *, 77> keywords
 */
constexpr std::array<const char *, 77> Token::m_keywords = {
    "abstract", "as", "base", "bool", "break", "byte", "case", "catch", "char", "checked", "class", "const", "continue", "decimal", "default", "delegate", "do", "double", "else", "enum", "event", "explicit", "extern", "false", "finally", "fixed", "float", "for", "foreach", "goto", "if", "implicit", "in", "int", "interface", "internal", "is", "lock", "long", "namespace", "new", "null", "object", "operator", "out", "override", "params", "private", "protected", "public", "readonly", "ref", "return", "sbyte", "sealed", "short", "sizeof", "stackalloc", "static", "string", "struct", "switch", "this", "throw", "true", "try", "typeof", "uint", "ulong", "unchecked", "unsafe", "ushort", "using", "virtual", "void", "volatile", "while"};

/**
 * @brief
 * Array of C# operators for the lexer
 * @constexpr std::array<const char *, 35> operators
 */
constexpr std::array<const char *, 40> Token::m_operators = {
    "+", "-", "*", "/", "%", "++", "--", "+=", "-=", "*=", "/=", "%=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", ">>=", "<<=", "&=", "|=", "^=", "??", "=>", "is", "as", ":", "::"};

/**
 * @brief
 * Array of C# separators for the lexer
 * @constexpr std::array<const char *, 12> separators
 */
constexpr std::array<const char *, 12> Token::m_separators = {
    "(", ")", "{", "}", "[", "]", ",", ";", ":", "?", ".", "::"};

/**
 * @brief
 * Array of C# comments for the lexer
 * @constexpr std::array<const char *, 3> comments
 * @note The last element is an empty string to avoid a bug in the lexer
 */
constexpr std::array<const char *, 4> Token::m_comments = {
    "//", "/*", "*/", ""};

/**
 * @brief
 * Array of C# literals for the lexer
 * @constexpr std::array<const char *, 5> literals
 */
constexpr std::array<const char *, 5> Token::m_literals = {
    "true", "false", "null", "this", "base"};

/**
 * @brief
 * Array of C# preprocessor directives for the lexer
 * @constexpr std::array<const char *, 12> preprocessor_directives
 */
constexpr std::array<const char *, 12> Token::m_preprocessor = {
    "#define", "#undef", "#if", "#ifdef", "#ifndef", "#else", "#elif", "#endif",
    "#error", "#warning", "#line", "#pragma"};

/**
 * @brief
 * Array of C# contextual keywords for the lexer
 * @constexpr std::array<const char *, 3> contextual_keywords
 */
constexpr std::array<const char *, 3> Token::m_contextual_keywords = {
    "var", "nameof", "yield"};

// Array data for the tokens (advanced)
/**
 * @brief
 * Array of C# access specifiers for the lexer
 * @constexpr std::array<const char *, 6> access_specifiers
 */
constexpr std::array<const char *, 6> Token::m_access_specifiers = {
    "public", "private", "protected", "internal", "protected internal", "private protected"};

/**
 * @brief
 * Array of C# attribute targets for the lexer
 * @constexpr std::array<const char *, 4> attribute_targets
 */
constexpr std::array<const char *, 4> Token::m_attribute_targets = {
    "assembly", "field", "method", "return"};

/**
 * @brief
 * Array of C# attribute usages for the lexer
 * @constexpr std::array<const char *, 3> attribute_usages
 */
constexpr std::array<const char *, 3> Token::m_attribute_usage = {
    "attribute", "extern", "assembly"};

/**
 * @brief
 * Array of C# escaped identifiers for the lexer
 * @constexpr std::array<const char *, 2> escaped_identifiers
 */
constexpr std::array<const char *, 2> Token::m_escaped_identifiers = {
    "@", "__arglist"};

/**
 * @brief
 * Array of C# interpolated strings for the lexer
 * @constexpr std::array<const char *, 2> interpolated_strings
 */
constexpr std::array<const char *, 2> Token::m_interpolated_strings = {
    "$", "@$"};

/**
 * @brief
 * Array of C# nullables for the lexer
 * @constexpr std::array<const char *, 2> nullables
 */
constexpr std::array<const char *, 2> Token::m_nullables = {
    "?", "??"};

/**
 * @brief
 * Array of C# preprocessor directives for the lexer
 * @constexpr std::array<const char *, 12> preprocessor_directives
 */
constexpr std::array<const char *, 2> Token::m_verbatim_strings = {
    "@", "@\"\""};

// Constructor
/**
 * @brief
 * Construct a new Token:: Token object
 * @param value The value of the token (e.g. "string")
 * @param type The type of the token (e.g. TokenType::)
 */
Token::Token(std::string value, TokenType type)
{
    this->m_value = value;
    this->m_type = type;
}

// Access methods
/**
 * @brief
 * Get the value of the token
 * @return std::string The value of the token
 */
std::string Token::get_value() const
{
    return this->m_value;
}

/**
 * @brief
 * Get the type of the token
 * @return TokenType The type of the token
 */
TokenType Token::get_type() const
{
    return this->m_type;
}

// Mutator methods
/**
 * @brief
 * Set the value of the token
 * @param value The value of the token
 */
void Token::set_value(std::string value)
{
    this->m_value = value;
}

/**
 * @brief
 * Set the type of the token
 * @param type The type of the token
 */
void Token::set_type(TokenType type)
{
    this->m_type = type;
}

// Functions
/**
 * @brief
 * Prints the token to the console in a readable format
 * @return std::string The token in a readable format
 */
std::string Token::to_string() const
{
    std::istringstream iss(this->m_value);
    std::ostringstream oss;
    std::string token;

    while (std::getline(iss, token, ' '))
    {
        if (is_keyword())
            oss << "Keyword: " << token << std::endl;
        else if (is_operator())
            oss << "Operator: " << token << std::endl;
        else if (is_separator())
            oss << "Separator: " << token << std::endl;
        else if (is_comment())
            oss << "Comment: " << token << std::endl;
        else if (is_literal())
            oss << "Literal: " << token << std::endl;
        else if (is_preprocessor())
            oss << "Preprocessor: " << token << std::endl;
        else if (is_contextual_keyword())
            oss << "Contextual Keyword: " << token << std::endl;
        else if (is_access_specifier())
            oss << "Access Specifier: " << token << std::endl;
        else if (is_attribute_target())
            oss << "Attribute Target: " << token << std::endl;
        else if (is_attribute_usage())
            oss << "Attribute Usage: " << token << std::endl;
        else if (is_escaped_identifier())
            oss << "Escaped Identifier: " << token << std::endl;
        else if (is_interpolated_string())
            oss << "Interpolated String: " << token << std::endl;
        else if (is_nullable())
            oss << "Nullable: " << token << std::endl;
        else if (is_verbatim_string())
            oss << "Verbatim String: " << token << std::endl;
        else
            oss << "Identifier: " << token << std::endl;
    }

    return oss.str();
}

/**
 * @brief
 * Checks if the token is a keyword
 * @return true The token is a keyword
 * @return false The token is not a keyword
 */
bool Token::is_keyword() const
{
    return std::find(m_keywords.begin(),
                     m_keywords.end(),
                     this->m_value) != m_keywords.end();
}

/**
 * @brief
 * Checks if the token is an operator
 * @return true The token is an operator
 * @return false The token is not an operator
 */
bool Token::is_operator() const
{
    return std::find(m_operators.begin(),
                     m_operators.end(),
                     this->m_value) != m_operators.end();
}

/**
 * @brief
 * Checks if the token is a separator
 * @return true The token is a separator
 * @return false The token is not a separator
 */
bool Token::is_separator() const
{
    return std::find(m_separators.begin(),
                     m_separators.end(),
                     this->m_value) != m_separators.end();
}

/**
 * @brief
 * Checks if the token is a comment
 * @return true The token is a comment
 * @return false The token is not a comment
 */
bool Token::is_comment() const
{
    return std::find(m_comments.begin(),
                     m_comments.end(),
                     this->m_value) != m_comments.end();
}

/**
 * @brief
 * Checks if the token is a literal
 * @return true The token is a literal
 * @return false The token is not a literal
 */
bool Token::is_literal() const
{
    return std::find(m_literals.begin(),
                     m_literals.end(),
                     this->m_value) != m_literals.end();
}

/**
 * @brief
 * Checks if the token is an identifier
 * @return true The token is an identifier
 * @return false The token is not an identifier
 */
bool Token::is_identifier() const
{
    return !this->is_keyword() && !this->is_operator() &&
           !this->is_separator() && !this->is_comment() &&
           !this->is_literal();
}

/**
 * @brief
 * Checks if the token is a preprocessor
 * @return true The token is a preprocessor
 * @return false The token is not a preprocessor
 */
bool Token::is_preprocessor() const
{
    return std::find(m_preprocessor.begin(),
                     m_preprocessor.end(),
                     this->m_value) != m_preprocessor.end();
}

/**
 * @brief
 * Checks if the token is a contextual keyword
 * @return true The token is a contextual keyword
 * @return false The token is not a contextual keyword
 */
bool Token::is_contextual_keyword() const
{
    return std::find(m_contextual_keywords.begin(),
                     m_contextual_keywords.end(),
                     this->m_value) != m_contextual_keywords.end();
}

/**
 * @brief
 * Checks if the token is an access specifier
 * @return true The token is an access specifier
 * @return false The token is not an access specifier
 */
bool Token::is_access_specifier() const
{
    return std::find(m_access_specifiers.begin(),
                     m_access_specifiers.end(),
                     this->m_value) != m_access_specifiers.end();
}

/**
 * @brief
 * Checks if the token is an attribute target
 * @return true The token is an attribute target
 * @return false The token is not an attribute target
 */
bool Token::is_attribute_target() const
{
    return std::find(m_attribute_targets.begin(),
                     m_attribute_targets.end(),
                     this->m_value) != m_attribute_targets.end();
}

/**
 * @brief
 * Checks if the token is an attribute usage
 * @return true The token is an attribute usage
 * @return false The token is not an attribute usage
 */
bool Token::is_attribute_usage() const
{
    return std::find(m_attribute_usage.begin(),
                     m_attribute_usage.end(),
                     this->m_value) != m_attribute_usage.end();
}

/**
 * @brief
 * Checks if the token is an escaped identifier
 * @return true The token is an escaped identifier
 * @return false The token is not an escaped identifier
 */
bool Token::is_escaped_identifier() const
{
    return std::find(m_escaped_identifiers.begin(),
                     m_escaped_identifiers.end(),
                     this->m_value) != m_escaped_identifiers.end();
}

/**
 * @brief
 * Checks if the token is an interpolated string
 * @return true The token is an interpolated string
 * @return false The token is not an interpolated string
 */
bool Token::is_interpolated_string() const
{
    return std::find(m_interpolated_strings.begin(),
                     m_interpolated_strings.end(),
                     this->m_value) != m_interpolated_strings.end();
}

/**
 * @brief
 * Checks if the token is a nullable
 * @return true The token is a nullable
 * @return false The token is not a nullable
 */
bool Token::is_nullable() const
{
    return std::find(m_nullables.begin(),
                     m_nullables.end(),
                     this->m_value) != m_nullables.end();
}

/**
 * @brief
 * Checks if the token is a verbatim string
 * @return true The token is a verbatim string
 * @return false The token is not a verbatim string
 */
bool Token::is_verbatim_string() const
{
    return std::find(m_verbatim_strings.begin(),
                     m_verbatim_strings.end(),
                     this->m_value) != m_verbatim_strings.end();
}
