//
//  basehangul.h
//  libbasehangul
//
//  Created by Gyusun Yeom on 2014. 11. 6..
//
//

#ifndef __BASE_HANGUL_H_
#define __BASE_HANGUL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "type.h"
#include <string.h>

/**
 * \brief Calculate size of data when encoded
 *
 * \param[in] inputSize Size of data to encode
 * \return              Size of encoded data
 */
size_t BaseHangulEncodeLength(size_t inputSize);

/**
 * \brief Encode data using basehangul method
 *
 * \param[out] encoded Array for encoded data
 * \param[in]  input   Data to encode
 * \param[in]  len     Length of \ref input
 * \return             Length of \ref encoded
 */
size_t BaseHangulEncode(unsigned char *encoded, const unsigned char *input, size_t len);

/**
 * \brief Decode basehangul encoded data
 *
 * \param[out] decoded
 * \param[in]  encoded Basehangul encoded data
 * \param[in]  len     Length of \ref encoded
 * \return             Length of \ref decoded
 */
size_t BaseHangulDecode(unsigned char *decoded, const unsigned char *encoded, size_t len);
    
const unsigned char *BaseHangulEncodeBlock(uint16_t *encoded, const unsigned char *input, size_t len);
    
#ifdef __cplusplus
}
#endif

#endif //__BASE_HANGUL_H_
