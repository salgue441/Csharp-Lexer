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