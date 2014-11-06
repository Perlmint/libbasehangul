#include "gtest/gtest.h"
#include "basehangul.h"

TEST(TestFromExample, BasicBlock)
{
    unsigned char data[5] = {49, 50, 51, 97, 98};
    
    uint16_t encoded[4] = {0};
    BaseHangulEncodeBlock(encoded, data, 5);
    
    ASSERT_EQ(encoded[0], 44733);
    ASSERT_EQ(encoded[1], 47673);
    ASSERT_EQ(encoded[2], 44813);
    ASSERT_EQ(encoded[3], 45404);
}

TEST(TestFromExample, Padding)
{
    unsigned char data[1] = {49};
    
    uint16_t encoded[4] = {0};
    BaseHangulEncodeBlock(encoded, data, 1);
    
    ASSERT_EQ(encoded[0], 44733);
    ASSERT_EQ(encoded[1], 55120);
    ASSERT_EQ(encoded[2], 55120);
    ASSERT_EQ(encoded[3], 55120);
}

TEST(TestFromExample, SpecialPadding)
{
    unsigned char data[4] = {49, 50, 51, 97};
    
    uint16_t encoded[4] = {0};
    BaseHangulEncodeBlock(encoded, data, 4);
    
    ASSERT_EQ(encoded[0], 44733);
    ASSERT_EQ(encoded[1], 47673);
    ASSERT_EQ(encoded[2], 44813);
    ASSERT_EQ(encoded[3], 48718);
}