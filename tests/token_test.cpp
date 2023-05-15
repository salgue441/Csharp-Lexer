/**
 * @file token_test.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the TokenTest class
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "token_test.h"

// Methods
/**
 * @brief
 * Sets up the test fixture
 */
void TokenTest::SetUp()
{
    // Set up test data
    token_keyword = Token("class", TokenType::Keyword);
    token_identifier = Token("myVar", TokenType::Identifier);
    token_literal = Token("42", TokenType::NumericLiteral);
    token_operator = Token("=", TokenType::Operator);
    token_separator = Token(";", TokenType::Separator);
    token_comment = Token("// this is a comment", TokenType::Comment);
    token_preprocessor = Token("#define", TokenType::Preprocessor);
    token_contextual_keyword = Token("var", TokenType::ContextualKeyword);
    token_access_specifier = Token("public", TokenType::AccessSpecifier);
    token_attribute_target = Token("field", TokenType::AttributeTarget);
    token_attribute_usage = Token("attribute", TokenType::AttributeUsage);
    token_escaped_identifier = Token("@myVar", TokenType::EscapedIdentifier);
    token_other = Token("???", TokenType::Other);
    token_nullable = Token("int?", TokenType::NullLiteral);
    token_regular_expression = Token("/[a-z]+/",
                                     TokenType::RegularExpressionLiteral);

    token_numeric_literal = Token("42", TokenType::NumericLiteral);

    token_interpolated_string =
        Token("$\"Hello, {name}!\"", TokenType::InterpolatedStringLiteral);

    token_verbatim_string =
        Token("@\"This is a verbatim string.\"", TokenType::VerbatimStringLiteral);
}

// Tests for the Token class]
/**
 * @brief
 * Checks that the Token class handles an empty string value correctly
 * @param TokenTest - Test fixture
 * @param EmptyStringValue - Test name
 */
TEST_F(TokenTest, EmptyStringValue)
{
    Token token("", TokenType::Identifier);
    EXPECT_EQ(token.get_value(), "");
    EXPECT_EQ(token.get_type(), TokenType::Identifier);
    EXPECT_EQ(token.to_string(), "Identifier: ");
}

/**
 * @brief
 * Checks that the Token class handles an empty TokenType correctly
 * @param TokenTest - Test fixture
 * @param EmptyTokenType - Test name
 */
TEST_F(TokenTest, EmptyTokenType)
{
    Token token("test", TokenType::Other);
    EXPECT_EQ(token.get_value(), "test");
    EXPECT_EQ(token.get_type(), TokenType::Other);
    EXPECT_EQ(token.to_string(), "Other: test");
}

/**
 * @brief
 * Checks if the constructor of the Token class works as expected
 * @param TokenTest - Test fixture
 * @param Constructor - Test name
 */
TEST_F(TokenTest, ConstructorTest)
{
    Token token1("", TokenType::Other);
    EXPECT_EQ(token1.get_value(), "");
    EXPECT_EQ(token1.get_type(), TokenType::Other);

    Token token2("test", TokenType::Identifier);
    EXPECT_EQ(token2.get_value(), "test");
    EXPECT_EQ(token2.get_type(), TokenType::Identifier);

    Token token3("=", TokenType::Operator);
    EXPECT_EQ(token3.get_value(), "=");
    EXPECT_EQ(token3.get_type(), TokenType::Operator);
}

/**
 * @brief
 * Checks that the access methods of the Token class work as expected
 * @param TokenTest - Test fixture
 * @param AccessMethods - Test name
 */
TEST_F(TokenTest, AccessMethods)
{
    EXPECT_EQ(token_keyword.get_value(), "class");
    EXPECT_EQ(token_keyword.get_type(), TokenType::Keyword);
    EXPECT_EQ(token_literal.get_value(), "42");
    EXPECT_EQ(token_literal.get_type(), TokenType::NumericLiteral);
    EXPECT_EQ(token_operator.get_value(), "=");
    EXPECT_EQ(token_operator.get_type(), TokenType::Operator);
    EXPECT_EQ(token_separator.get_value(), ";");
    EXPECT_EQ(token_separator.get_type(), TokenType::Separator);
    EXPECT_EQ(token_comment.get_value(), "// this is a comment");
    EXPECT_EQ(token_comment.get_type(), TokenType::Comment);
    EXPECT_EQ(token_preprocessor.get_value(), "#define");
    EXPECT_EQ(token_preprocessor.get_type(), TokenType::Preprocessor);
    EXPECT_EQ(token_contextual_keyword.get_value(), "var");
    EXPECT_EQ(token_contextual_keyword.get_type(),
              TokenType::ContextualKeyword);
    EXPECT_EQ(token_access_specifier.get_value(), "public");
    EXPECT_EQ(token_access_specifier.get_type(), TokenType::AccessSpecifier);
    EXPECT_EQ(token_attribute_target.get_value(), "field");
    EXPECT_EQ(token_attribute_target.get_type(), TokenType::AttributeTarget);
    EXPECT_EQ(token_attribute_usage.get_value(), "attribute");
    EXPECT_EQ(token_attribute_usage.get_type(), TokenType::AttributeUsage);
    EXPECT_EQ(token_escaped_identifier.get_value(), "@myVar");
    EXPECT_EQ(token_escaped_identifier.get_type(),
              TokenType::EscapedIdentifier);
    EXPECT_EQ(token_interpolated_string.get_value(), "$\"Hello, {name}!\"");
    EXPECT_EQ(token_interpolated_string.get_type(),
              TokenType::InterpolatedStringLiteral);
    EXPECT_EQ(token_nullable.get_value(), "int?");
    EXPECT_EQ(token_nullable.get_type(), TokenType::NullLiteral);
    EXPECT_EQ(token_verbatim_string.get_value(),
              "@\"This is a verbatim string.\"");
    EXPECT_EQ(token_verbatim_string.get_type(), TokenType::VerbatimStringLiteral);
    EXPECT_EQ(token_other.get_value(), "???");
    EXPECT_EQ(token_regular_expression.get_value(), "/[a-z]+/");
    EXPECT_EQ(token_other.get_type(), TokenType::Other);
}

/**
 * @brief
 * Checks that the mutator methods of the Token class work as expected
 * @param TokenTest - Test fixture
 * @param MutatorMethods - Test name
 */
TEST_F(TokenTest, MutatorMethods)
{
    token_keyword.set_value("struct");
    token_keyword.set_type(TokenType::Identifier);
    EXPECT_EQ(token_keyword.get_value(), "struct");
    EXPECT_EQ(token_keyword.get_type(), TokenType::Identifier);
}

/**
 * @brief
 * Checks that the methods work as expected
 * @param TokenTest - Test fixture
 * @param TokenTypeFunctions - Test name
 */
TEST_F(TokenTest, TokenTypeFunctions)
{
    EXPECT_TRUE(token_keyword.is_keyword());
    EXPECT_TRUE(token_identifier.is_identifier());
    EXPECT_TRUE(token_literal.is_numeric_literal());
    EXPECT_TRUE(token_operator.is_operator());
    EXPECT_TRUE(token_separator.is_separator());
    EXPECT_TRUE(token_comment.is_comment());
    EXPECT_TRUE(token_preprocessor.is_preprocessor());
    EXPECT_TRUE(token_contextual_keyword.is_contextual_keyword());
    EXPECT_TRUE(token_access_specifier.is_access_specifier());
    EXPECT_TRUE(token_attribute_target.is_attribute_target());
    EXPECT_TRUE(token_attribute_usage.is_attribute_usage());
    EXPECT_TRUE(token_escaped_identifier.is_escaped_identifier());
    EXPECT_TRUE(token_interpolated_string.is_interpolated_string());
    EXPECT_TRUE(token_nullable.is_nullable());
    EXPECT_TRUE(token_verbatim_string.is_verbatim_string());
    EXPECT_TRUE(token_regular_expression.is_regular_expression());
    EXPECT_TRUE(token_other.get_type() == TokenType::Other);
}

/**
 * @brief
 * Checks that the to_string method works as expected
 * @param TokenTest - Test fixture
 * @param ToStringTest - Test name
 */
TEST_F(TokenTest, ToStringTest)
{
    Token token("hello", TokenType::Identifier);
    EXPECT_EQ(token.to_string(), "Identifier: hello");

    token.set_type(TokenType::Keyword);
    token.set_value("if");
    EXPECT_EQ(token.to_string(), "Keyword: if");

    token.set_type(TokenType::NumericLiteral);
    token.set_value("42");
    EXPECT_EQ(token.to_string(), "NumericLiteral: 42");

    token.set_type(TokenType::Operator);
    token.set_value("+");
    EXPECT_EQ(token.to_string(), "Operator: +");

    token.set_type(TokenType::Separator);
    token.set_value(",");
    EXPECT_EQ(token.to_string(), "Separator: ,");

    token.set_type(TokenType::Comment);
    token.set_value("// hello");
    EXPECT_EQ(token.to_string(), "Comment: // hello");

    token.set_type(TokenType::VerbatimStringLiteral);
    token.set_value("\"hello world\"");
    EXPECT_EQ(token.to_string(), "VerbatimStringLiteral: \"hello world\"");

    token.set_type(TokenType::InterpolatedStringLiteral);
    token.set_value("$\"hello {name}\"");
    EXPECT_EQ(token.to_string(), "InterpolatedStringLiteral: $\"hello {name}\"");

    token.set_type(TokenType::EscapedIdentifier);
    token.set_value("@hello");
    EXPECT_EQ(token.to_string(), "EscapedIdentifier: @hello");

    token.set_type(TokenType::Preprocessor);
    token.set_value("#define");
    EXPECT_EQ(token.to_string(), "Preprocessor: #define");

    token.set_type(TokenType::ContextualKeyword);
    token.set_value("get");
    EXPECT_EQ(token.to_string(), "ContextualKeyword: get");

    token.set_type(TokenType::AccessSpecifier);
    token.set_value("public");
    EXPECT_EQ(token.to_string(), "AccessSpecifier: public");

    token.set_type(TokenType::AttributeTarget);
    token.set_value("assembly");
    EXPECT_EQ(token.to_string(), "AttributeTarget: assembly");

    token.set_type(TokenType::AttributeUsage);
    token.set_value("Obsolete");
    EXPECT_EQ(token.to_string(), "AttributeUsage: Obsolete");

    token.set_type(TokenType::NullLiteral);
    token.set_value("int?");
    EXPECT_EQ(token.to_string(), "NullLiteral: int?");

    token.set_type(TokenType::RegularExpressionLiteral);
    token.set_value("/[a-z]+/");
    EXPECT_EQ(token.to_string(), "RegularExpressionLiteral: /[a-z]+/");

    token.set_type(TokenType::Other);
    token.set_value("foo");
    EXPECT_EQ(token.to_string(), "Other: foo");
}

/**
 * @brief Checks that the Token class handles a null string value correctly
 * @param TokenTest - Test fixture
 * @param NullStringValue - Test name
 */
TEST_F(TokenTest, NullStringValue)
{
    Token token("", TokenType::Identifier);
    EXPECT_EQ(token.get_value(), "");
    EXPECT_EQ(token.get_type(), TokenType::Identifier);
    EXPECT_EQ(token.to_string(), "Identifier: ");
}

/**
 * @brief Checks that the Token class handles a null TokenType correctly
 * @param TokenTest - Test fixture
 * @param NullTokenType - Test name
 */
TEST_F(TokenTest, NullTokenType)
{
    Token token("test", std::nullopt);
    EXPECT_EQ(token.get_value(), "test");
    EXPECT_EQ(token.get_type(), TokenType::Other);
    EXPECT_EQ(token.to_string(), "Other: test");
}

/**
 * @brief Checks that the Token class handles a different value and TokenType correctly
 * @param TokenTest - Test fixture
 * @param DifferentValueAndTokenType - Test name
 */
TEST_F(TokenTest, DifferentValueAndTokenType)
{
    Token token("test", TokenType::Identifier);
    EXPECT_EQ(token.get_value(), "test");
    EXPECT_EQ(token.get_type(), TokenType::Identifier);
    EXPECT_EQ(token.to_string(), "Identifier: test");

    token.set_value("1234");
    token.set_type(TokenType::NumericLiteral);
    EXPECT_EQ(token.get_value(), "1234");
    EXPECT_EQ(token.get_type(), TokenType::NumericLiteral);
    EXPECT_EQ(token.to_string(), "NumericLiteral: 1234");
}

/**
 * @brief Checks that the Token class handles a special character value correctly
 * @param TokenTest - Test fixture
 * @param SpecialCharacterValue - Test name
 */
TEST_F(TokenTest, SpecialCharacterValue)
{
    Token token("&", TokenType::Operator);
    EXPECT_EQ(token.get_value(), "&");
    EXPECT_EQ(token.get_type(), TokenType::Operator);
    EXPECT_EQ(token.to_string(), "Operator: &");
}

/**
 * @brief Checks that the Token class handles a large string value correctly
 * @param TokenTest - Test fixture
 * @param LargeStringValue - Test name
 */
TEST_F(TokenTest, LargeStringValue)
{
    std::string long_string(100000, 'a');
    Token token(long_string, TokenType::Identifier);
    EXPECT_EQ(token.get_value(), long_string);
    EXPECT_EQ(token.get_type(), TokenType::Identifier);
    EXPECT_EQ(token.to_string(), "Identifier: " + long_string);
}
