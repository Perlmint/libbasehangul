//
//  test_example_decode.cc
//  libbasehangul
//
//  Created by Gyusun Yeom on 2014. 11. 9..
//
//

#include "gtest/gtest.h"
#include "basehangul.h"

TEST(BlockDecodeTestFromExample, BasicBlock)
{
    uint16_t encoded[4] = {44733, 47673, 44813, 45404};
    unsigned char decoded[5] = {0};
    BaseHangulDecodeBlock(decoded, encoded, 4);
    
    ASSERT_EQ(decoded[0], 49);
    ASSERT_EQ(decoded[1], 50);
    ASSERT_EQ(decoded[2], 51);
    ASSERT_EQ(decoded[3], 97);
    ASSERT_EQ(decoded[4], 98);
}

TEST(BlockDecodeTestFromExample, PaddingBy)
{
    uint16_t encoded[4] = {44733, 55120, 55120, 55120};
    unsigned char decoded[5] = {0};
    BaseHangulDecodeBlock(decoded, encoded, 4);
    
    ASSERT_EQ(decoded[0], 49);
}

TEST(BlockDecodeTestFromExample, SpecialPadding)
{
    uint16_t encoded[4] = {44733, 47673, 44816, 48718};
    unsigned char decoded[5] = {0};
    BaseHangulDecodeBlock(decoded, encoded, 4);
    
    ASSERT_EQ(decoded[0], 49);
    ASSERT_EQ(decoded[1], 50);
    ASSERT_EQ(decoded[2], 51);
    ASSERT_EQ(decoded[3], 100);
}

TEST(DecodeTestFromExample, BasicBlock)
{
    unsigned char encoded[] = {0xea, 0xba, 0xbd, 0xeb, 0xa8, 0xb9, 0xea, 0xbc, 0x8d, 0xeb, 0x85, 0x9c, 0};
    unsigned char decoded[5] = {0};
    BaseHangulDecode(decoded, encoded, 4, UTF8);
    
    ASSERT_EQ(decoded[0], 49);
    ASSERT_EQ(decoded[1], 50);
    ASSERT_EQ(decoded[2], 51);
    ASSERT_EQ(decoded[3], 97);
    ASSERT_EQ(decoded[4], 98);
}

TEST(DecodeTestFromExample, PaddingBy)
{
    unsigned char encoded[] = {0xea, 0xba, 0xbd, 0xed, 0x9d, 0x90, 0xed, 0x9d, 0x90, 0xed, 0x9d, 0x90, 0};
    unsigned char decoded[1] = {0};
    BaseHangulDecode(decoded, encoded, 4, UTF8);
    
    ASSERT_EQ(decoded[0], 49);
}

TEST(DecodeTestFromExample, SpecialPadding)
{
    unsigned char encoded[] = {0xea, 0xba, 0xbd, 0xeb, 0xa8, 0xb9, 0xea, 0xbc, 0x90, 0xeb, 0xb9, 0x8e, 0};
    unsigned char decoded[4] = {0};
    BaseHangulDecode(decoded, encoded, 4, UTF8);
    
    ASSERT_EQ(decoded[0], 49);
    ASSERT_EQ(decoded[1], 50);
    ASSERT_EQ(decoded[2], 51);
    ASSERT_EQ(decoded[3], 100);
}