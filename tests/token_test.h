/**
 * @file token_test.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Definition of the TokenTest class
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 *
 */

// Google Test library
#include <gtest/gtest.h>

// Project files
#include "../src/token.h"

/**
 * @brief
 * Test fixture for the Token class
 * @class TokenTest
 * @extends ::testing::Test
 */
class TokenTest : public ::testing::Test
{
protected:
    // Test data
    Token token_keyword;
    Token token_identifier;
    Token token_literal;
    Token token_operator;
    Token token_separator;
    Token token_comment;
    Token token_preprocessor;
    Token token_contextual_keyword;
    Token token_access_specifier;
    Token token_attribute_target;
    Token token_attribute_usage;
    Token token_escaped_identifier;
    Token token_interpolated_string;
    Token token_nullable;
    Token token_verbatim_string;
    Token token_other;

    // Methods
    void SetUp() override;
};