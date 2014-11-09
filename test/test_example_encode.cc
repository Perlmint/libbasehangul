#include "gtest/gtest.h"
#include "basehangul.h"

TEST(BlockEncodeTestFromExample, BasicBlock)
{
    unsigned char data[5] = {49, 50, 51, 97, 98};
    
    uint16_t encoded[4] = {0};
    BaseHangulEncodeBlock(encoded, data, 5);
    
    ASSERT_EQ(encoded[0], 44733);
    ASSERT_EQ(encoded[1], 47673);
    ASSERT_EQ(encoded[2], 44813);
    ASSERT_EQ(encoded[3], 45404);
}

TEST(BlockEncodeTestFromExample, PaddingBy)
{
    unsigned char data[1] = {49};
    
    uint16_t encoded[4] = {0};
    BaseHangulEncodeBlock(encoded, data, 1);
    
    ASSERT_EQ(encoded[0], 44733);
    ASSERT_EQ(encoded[1], 55120);
    ASSERT_EQ(encoded[2], 55120);
    ASSERT_EQ(encoded[3], 55120);
}

TEST(BlockEncodeTestFromExample, SpecialPadding)
{
    unsigned char data[4] = {49, 50, 51, 100};
    
    uint16_t encoded[4] = {0};
    BaseHangulEncodeBlock(encoded, data, 4);
    
    ASSERT_EQ(encoded[0], 44733);
    ASSERT_EQ(encoded[1], 47673);
    ASSERT_EQ(encoded[2], 44816);
    ASSERT_EQ(encoded[3], 48718);
}

TEST(EncodeTestFromExample, BasicBlock)
{
    unsigned char data[5] = {49, 50, 51, 97, 98};
    
    unsigned char encoded[13] = {0};
    BaseHangulEncode(encoded, data, 5, UTF8);
    
    unsigned char correct[13] = {0xea, 0xba, 0xbd, 0xeb, 0xa8, 0xb9, 0xea, 0xbc, 0x8d, 0xeb, 0x85, 0x9c, 0};
    
    ASSERT_EQ(correct[0], encoded[0]);
    ASSERT_EQ(correct[1], encoded[1]);
    ASSERT_EQ(correct[2], encoded[2]);
    ASSERT_EQ(correct[3], encoded[3]);
    ASSERT_EQ(correct[4], encoded[4]);
    ASSERT_EQ(correct[5], encoded[5]);
    ASSERT_EQ(correct[6], encoded[6]);
    ASSERT_EQ(correct[7], encoded[7]);
    ASSERT_EQ(correct[8], encoded[8]);
    ASSERT_EQ(correct[9], encoded[9]);
    ASSERT_EQ(correct[10], encoded[10]);
    ASSERT_EQ(correct[11], encoded[11]);
    ASSERT_EQ(correct[12], encoded[12]);
}

TEST(EncodeTestFromExample, PaddingBy)
{
    unsigned char data[1] = {49};
    
    unsigned char encoded[13] = {0};
    BaseHangulEncode(encoded, data, 1, UTF8);
    
    unsigned char correct[13] = {0xea, 0xba, 0xbd, 0xed, 0x9d, 0x90, 0xed, 0x9d, 0x90, 0xed, 0x9d, 0x90, 0};
    
    ASSERT_EQ(correct[0], encoded[0]);
    ASSERT_EQ(correct[1], encoded[1]);
    ASSERT_EQ(correct[2], encoded[2]);
    ASSERT_EQ(correct[3], encoded[3]);
    ASSERT_EQ(correct[4], encoded[4]);
    ASSERT_EQ(correct[5], encoded[5]);
    ASSERT_EQ(correct[6], encoded[6]);
    ASSERT_EQ(correct[7], encoded[7]);
    ASSERT_EQ(correct[8], encoded[8]);
    ASSERT_EQ(correct[9], encoded[9]);
    ASSERT_EQ(correct[10], encoded[10]);
    ASSERT_EQ(correct[11], encoded[11]);
    ASSERT_EQ(correct[12], encoded[12]);
}

TEST(EncodeTestFromExample, SpecialPadding)
{
    unsigned char data[4] = {49, 50, 51, 100};
    
    unsigned char encoded[13] = {0};
    BaseHangulEncode(encoded, data, 4, UTF8);
    
    unsigned char correct[13] = {0xea, 0xba, 0xbd, 0xeb, 0xa8, 0xb9, 0xea, 0xbc, 0x90, 0xeb, 0xb9, 0x8e, 0};
    
    ASSERT_EQ(correct[0], encoded[0]);
    ASSERT_EQ(correct[1], encoded[1]);
    ASSERT_EQ(correct[2], encoded[2]);
    ASSERT_EQ(correct[3], encoded[3]);
    ASSERT_EQ(correct[4], encoded[4]);
    ASSERT_EQ(correct[5], encoded[5]);
    ASSERT_EQ(correct[6], encoded[6]);
    ASSERT_EQ(correct[7], encoded[7]);
    ASSERT_EQ(correct[8], encoded[8]);
    ASSERT_EQ(correct[9], encoded[9]);
    ASSERT_EQ(correct[10], encoded[10]);
    ASSERT_EQ(correct[11], encoded[11]);
    ASSERT_EQ(correct[12], encoded[12]);
}