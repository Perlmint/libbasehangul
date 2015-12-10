//
//  basehangul.c
//  libbasehangul
//
//  Created by Gyusun Yeom on 2014. 11. 6..
//
//

#include "basehangul.h"
#include "digit_set.h"
#include <assert.h>

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

size_t BaseHangulEncodeLength(size_t inputSize, Encoding encoding)
{
    uint8_t char_size = 2;
    switch (encoding) {
        case UCS2:
            char_size = 2;
            break;
        case UTF8:
            char_size = 3;
            break;
    }
    return ((inputSize / 5 * 4) + ((inputSize % 5) == 0 ? 0 : 4)) * char_size;
}

/**
 * Decode UCS2 and Encode into UTF-8
 *
 * \param[out] ouput UTF-8 string
 * \param[in]  input UCS2 string
 **/
void UCS2toUTF8(unsigned char *output, const uint16_t *input)
{
    for (uint8_t i = 0; i < 4; ++i)
    {
        output[i * 3 + 0] = 0xE0 | ((input[i] & 0xF000) >> 12);
        output[i * 3 + 1] = 0x80 | ((input[i] & 0x0FC0) >> 6);
        output[i * 3 + 2] = 0x80 | ((input[i] & 0x003F));
    }
}

/**
 * Decode UTF-8 and encode in UCS2(UTF-16)
 *
 * \param[out] output UCS2(UTF-16) string
 * \param[in]  input  UTF-8 string
 * \param[in]  len    UTF-8 string length
 **/
void UTF8toUCS2(uint16_t *output, const unsigned char *input, uint8_t len)
{
    len = min(len, 4);

    for (uint8_t i = 0; i < len; ++i)
    {
        output[i] =
            ((input[i * 3 + 0] & 0x0F) << 12) |
            ((input[i * 3 + 1] & 0x3F) << 6) |
            (input[i * 3 + 2] & 0x3F);
    }
}

size_t BaseHangulEncode(unsigned char *encoded, const unsigned char *input, size_t len, Encoding encoding)
{
    uint16_t buffer[4] = {0};

    size_t written = 0;
    for (size_t processed = 0, end = len; processed < end; processed += 5, written += 4)
    {
        memset(buffer, 0, sizeof(buffer));

        input = BaseHangulEncodeBlock(buffer, input, len - processed);

        switch (encoding) {
            case UCS2:
                memcpy(encoded, buffer, sizeof(buffer));
                encoded += sizeof(buffer);
                break;
            case UTF8:
                UCS2toUTF8(encoded, buffer);
                encoded += 4 * 3;
                break;
        }
    }

    return written;
}

size_t BaseHangulDecode(unsigned char *decoded, const unsigned char *encoded, size_t len, Encoding encoding)
{
    uint16_t inputbuffer[4] = {0};

    size_t written = 0;
    for (size_t processed = 0, end = len; processed < end;)
    {
        memset(inputbuffer, 0, sizeof(inputbuffer));

        uint8_t blockSize = 0;
        switch (encoding) {
            case UCS2:
                blockSize = min(len - processed, 5);
                memcpy(inputbuffer, encoded, blockSize * 2);
                encoded += blockSize;
                written += blockSize / 5 * 4;
                break;
            case UTF8:
                blockSize = min(len - processed, 15);
                UTF8toUCS2(inputbuffer, encoded, blockSize);
                encoded += blockSize;
                written += blockSize / 15 * 4;
                break;
        }

        BaseHangulDecodeBlock(decoded, inputbuffer, len - processed);

        processed += blockSize;
    }

    return written;
}

const unsigned char *BaseHangulEncodeBlock(uint16_t *encoded, const unsigned char *input, size_t len)
{
    if (len == 0)
    {
        return input;
    }

    unsigned char block[5] = {0};
    memcpy(block, input, len);

    encoded[0] = digit_set[(block[0] << 2) | (block[1] >> 6)];
    encoded[1] = digit_set[((block[1] & 0x3F) << 4) | (block[2] >> 4)];
    encoded[2] = digit_set[((block[2] & 0x0F) << 6) | (block[3] >> 2)];
    encoded[3] = digit_set[((block[3] & 0x03) << 8) | (block[4])];

    if (len == 4)
    {
        encoded[3] = digit_set[1024 + ((block[3] & 0x03) >> 8)];
    }
    else if (len <= 3)
    {
        for (uint8_t i = 3, to = len; i >= to ; --i)
        {
            encoded[i] = digit_set[1028];
        }
    }

    return input + min(len, 5);
}

/**
 * Get character index from basehangul set
 *
 * \param[in] ch  Single character
 * \returns       Index in basehangul set
 */
uint16_t CharcterToIndex(uint16_t ch)
{
    for (size_t i = 0, e = sizeof(digit_set) / sizeof(*digit_set); i < e; ++i) {
        if (digit_set[i] == ch)
        {
            if (i == 1027)
            {
                return 0;
            }
            else if (i > 1023)
            {
                return (i - 1024) << 8;
            }

            return i;
        }
    }

    assert(!"Invalid character for basehangul");
}

const uint16_t *BaseHangulDecodeBlock(unsigned char *decoded, const uint16_t *encoded, size_t len)
{
    if (len == 0)
    {
        return encoded;
    }

    uint16_t block[4] = {0};
    for (int i = 0, valid_block_size = min(len, 4); i < valid_block_size; ++i)
    {
        block[i] = CharcterToIndex(*encoded);
        ++encoded;
    }

    decoded[0] = block[0] >> 2;
    decoded[1] = ((block[0] & 0x0003) << 6) | (block[1] >> 4);
    if (len < 1 || block[1] == 0)
    {
        return encoded;
    }

    decoded[2] = ((block[1] & 0x000F) << 4) | (block[2] >> 6);
    if (len < 2 || block[2] == 0)
    {
        return encoded;
    }

    decoded[3] = ((block[2] & 0x003F) << 2) | (block[3] >> 8);
    if (len < 3 || block[3] == 0)
    {
        return encoded;
    }

    decoded[4] = (block[3] & 0x00FF);

    return encoded;
}
