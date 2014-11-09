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