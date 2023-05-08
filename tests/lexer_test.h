/**
 * @file lexer_test.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Definition of the LexerTest class
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 */

// Google Test library
#include <gtest/gtest.h>

// Project files
#include "../src/lexer.h"

/**
 * @brief
 * Test fixture for the Lexer class
 * @class LexerTest
 * @extends ::testing::Test
 */
class LexerTest : public ::testing::Test
{
protected:
    Lexer lexer;
    std::vector<Token> expected_tokens;

    // Methods
    void SetUp() override;
};