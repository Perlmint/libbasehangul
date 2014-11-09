//
//  basehangul.c
//  libbasehangul
//
//  Created by Gyusun Yeom on 2014. 11. 6..
//
//

#include "basehangul.h"
#include "digit_set.h"

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

void UCS2toUTF8(unsigned char *output, const uint16_t *input)
{
    for (uint8_t i = 0; i < 4; ++i)
    {
        output[i * 3 + 0] = 0xE0 | ((input[i] & 0xF000) >> 12);
        output[i * 3 + 1] = 0x80 | ((input[i] & 0x0FC0) >> 6);
        output[i * 3 + 2] = 0x80 | ((input[i] & 0x003F));
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
    // Not implemented yet
    return 0;
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
    
    return input;
}