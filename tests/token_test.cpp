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
void TokenTest::SetUp()
{
    // Set up test data
    token_keyword = Token("class", TokenType::Keyword);
    token_identifier = Token("myVar", TokenType::Identifier);
    token_literal = Token("42", TokenType::Literal);
    token_operator = Token("=", TokenType::Operator);
    token_separator = Token(";", TokenType::Separator);
    token_comment = Token("// this is a comment", TokenType::Comment);
    token_preprocessor = Token("#define", TokenType::Preprocessor);
    token_contextual_keyword = Token("var", TokenType::ContextualKeyword);
    token_access_specifier = Token("public", TokenType::AccessSpecifier);
    token_attribute_target = Token("field", TokenType::AttributeTarget);
    token_attribute_usage = Token("attribute", TokenType::AttributeUsage);
    token_escaped_identifier = Token("@myVar", TokenType::EscapedIdentifier);
    token_interpolated_string =
        Token("$\"Hello, {name}!\"", TokenType::InterpolatedStringLiteral);
    token_nullable = Token("int?", TokenType::NullLiteral);
    token_verbatim_string =
        Token("@\"This is a verbatim string.\"", TokenType::VerbatimStringLiteral);
    token_other = Token("???", TokenType::Other);
}

// Tests for the Token class
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
    EXPECT_EQ(token_literal.get_type(), TokenType::Literal);
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