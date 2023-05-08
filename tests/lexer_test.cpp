/**
 * @file lexer_test.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the LexerTest class
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lexer_test.h"

// Methods
/**
 * @brief
 * Set up the test fixture.
 * @details The expected tokens are a simple C# program.
 */
void LexerTest::SetUp()
{
    expected_tokens = {
        Token("using", TokenType::Keyword),
        Token("System", TokenType::Identifier),
        Token(";", TokenType::Separator),
        Token("namespace", TokenType::Keyword),
        Token("HelloWorld", TokenType::Identifier),
        Token("{", TokenType::Separator),
        Token("class", TokenType::Keyword),
        Token("Program", TokenType::Identifier),
        Token("{", TokenType::Separator),
        Token("static", TokenType::Keyword),
        Token("void", TokenType::Keyword),
        Token("Main", TokenType::Identifier),
        Token("(", TokenType::Separator),
        Token("string", TokenType::Keyword),
        Token("[]", TokenType::Separator),
        Token("args", TokenType::Identifier),
        Token(")", TokenType::Separator),
        Token("{", TokenType::Separator),
        Token("Console", TokenType::Identifier),
        Token(".", TokenType::Separator),
        Token("WriteLine", TokenType::Identifier),
        Token("(", TokenType::Separator),
        Token("\"Hello World!\"", TokenType::InterpolatedStringLiteral),
        Token(")", TokenType::Separator),
        Token(";", TokenType::Separator),
        Token("}", TokenType::Separator),
        Token("}", TokenType::Separator),
        Token("}", TokenType::Separator),
    };
}

// Tests
/**
 * @brief
 * Test the lexing of a simple C# program.
 * @param LexerTest - Test fixture
 * @param HelloWorld - Test name
 */
TEST(LexerTest, HelloWorld)
{
    Lexer lexer;
    std::string filename = "helloworld.cs";

    std::vector<Token> expected_tokens = {
        Token("using", TokenType::Keyword),
        Token("System", TokenType::Identifier),
        Token(";", TokenType::Separator),
        Token("namespace", TokenType::Keyword),
        Token("HelloWorld", TokenType::Identifier),
        Token("{", TokenType::Separator),
        Token("class", TokenType::Keyword),
        Token("Program", TokenType::Identifier),
        Token("{", TokenType::Separator),
        Token("static", TokenType::Keyword),
        Token("void", TokenType::Keyword),
        Token("Main", TokenType::Identifier),
        Token("(", TokenType::Separator),
        Token("string", TokenType::Keyword),
        Token("[]", TokenType::Separator),
        Token("args", TokenType::Identifier),
        Token(")", TokenType::Separator),
        Token("{", TokenType::Separator),
        Token("Console", TokenType::Identifier),
        Token(".", TokenType::Separator),
        Token("WriteLine", TokenType::Identifier),
        Token("(", TokenType::Separator),
        Token("\"Hello World!\"", TokenType::VerbatimStringLiteral),
        Token(")", TokenType::Separator),
        Token(";", TokenType::Separator),
        Token("}", TokenType::Separator),
        Token("}", TokenType::Separator),
        Token("}", TokenType::Separator),
    };

    std::vector<std::string> files = {filename};
    lexer.lex_files(files);

    ASSERT_EQ(lexer.get_tokens_from_file(filename), expected_tokens);
}
