//
//  basehangul.c
//  libbasehangul
//
//  Created by Gyusun Yeom on 2014. 11. 6..
//
//

#include "basehangul.h"
#include "digit_set.h"

size_t BaseHangulEncodeLength(size_t inputSize)
{
    return (inputSize / 5 * 4) + ((inputSize % 5) == 0 ? 0 : 4);
}

size_t BaseHangulEncode(unsigned char *encoded, const unsigned char *input, size_t len)
{
    uint16_t buffer[4] = {0};
    
    size_t written = 0;
    for (size_t processed = 0, end = len - 4; processed < end; processed += 5, written += 4)
    {
        memset(buffer, 0, sizeof(buffer));
        
        input = BaseHangulEncodeBlock(buffer, input, len - processed);
        
        memcpy(encoded, buffer, sizeof(buffer));
        encoded += sizeof(buffer);
    }
    
    return written;
}

size_t BaseHangulDecode(unsigned char *decoded, const unsigned char *encoded, size_t len)
{
    // Not implemented yet
    return 0;
}

const unsigned char *BaseHangulEncodeBlock(uint16_t *encoded, const unsigned char *input, size_t len)
{
    if (len == 0)
    {
        return input;
    }
    
    if (len == 4)
    {
        encoded[0] = digit_set[(input[0] << 2) | (input[1] >> 6)];
        encoded[1] = digit_set[((input[1] & 0x3F) << 4) | (input[2] >> 4)];
        encoded[2] = digit_set[((input[2] & 0x0F) << 6) | (input[3] >> 2)];
        encoded[3] = digit_set[1024 + ((input[3] & 0x03) >> 8)];
    }
    else if (len == 3)
    {
        encoded[0] = digit_set[(input[0] << 2) | (input[1] >> 6)];
        encoded[1] = digit_set[((input[1] & 0x3F) << 4) | (input[2] >> 4)];
        encoded[2] = digit_set[((input[2] & 0x0F) << 6)];
        encoded[3] = digit_set[1028];
    }
    else if (len == 2)
    {
        encoded[0] = digit_set[(input[0] << 2) | (input[1] >> 6)];
        encoded[1] = digit_set[((input[1] & 0x3F) << 4)];
        encoded[2] = digit_set[1028];
        encoded[3] = digit_set[1028];
    }
    else if (len == 1)
    {
        encoded[0] = digit_set[input[0] << 2];
        encoded[1] = digit_set[1028];
        encoded[2] = digit_set[1028];
        encoded[3] = digit_set[1028];
    }
    else
    {
        encoded[0] = digit_set[(input[0] << 2) | (input[1] >> 6)];
        encoded[1] = digit_set[((input[1] & 0x3F) << 4) | (input[2] >> 4)];
        encoded[2] = digit_set[((input[2] & 0x0F) << 6) | (input[3] >> 2)];
        encoded[3] = digit_set[((input[3] & 0x03) << 8) | (input[4])];
    }
    
    return input;
}