//
//  basehangul.h
//  libbasehangul
//
//  Created by Gyusun Yeom on 2014. 11. 6..
//
// \defgroup encoding
// \defgroup decoding

#ifndef __BASE_HANGUL_H_
#define __BASE_HANGUL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "type.h"
#include <string.h>

/// Output encoding method
typedef enum
{
    /// UCS2 or UTF-16
    UCS2,
    /// UTF-8
    UTF8
} Encoding;

/// \addtogroup encoding
/// @{

/**
 * \brief Calculate size of data when encoded
 *
 * \param[in] inputSize Size of data to encode
 * \param[in] encoding  output encoding
 * \return              Size of encoded data
 */
size_t BaseHangulEncodeLength(size_t inputSize, Encoding encoding);

/**
 * \brief Encode data using basehangul method
 *
 * \param[out] encoded     Array for encoded data
 * \param[in]  input       Data to encode
 * \param[in]  len         Length of \p input
 * \param[in]  encoding    Character Encoding Type
 * \return                 Length of \p encoded
 */
size_t BaseHangulEncode(unsigned char *encoded, const unsigned char *input, size_t len, Encoding encoding);

/// @}
/// \addtogroup decoding
/// @{

/**
 * \brief Decode basehangul encoded data
 *
 * \param[out] decoded
 * \param[in]  encoded    Basehangul encoded data
 * \param[in]  len        Length of \p encoded
 * \param[in]  encoding   Encoding of \p encoded
 * \return                Length of \p decoded
 */
size_t BaseHangulDecode(unsigned char *decoded, const unsigned char *encoded, size_t len, Encoding encoding);

/// @}
/// \addtogroup encoding
/// @{

/**
 * \brief Decode basehangul encoded data block(max 5byte)
 *
 * \param[out] decoded decoded data of \p encoded
 * \param[in]  encoded encoded data (UCS2)
 * \param[in]  len     encoded block size(2byte)
 * \return             pointer of encoded data
 */
const uint16_t *BaseHangulDecodeBlock(unsigned char *decoded, const uint16_t *encoded, size_t len);

/// @}
/// \addtogroup decoding
/// @{

/**
 * \brief Encode data block(max 4byte)
 *
 * \param[out] encoded Basehangul encoded data
 * \param[in]  input   raw data to encode
 * \param[in]  len     Size of \p input
 * \return
 */
const unsigned char *BaseHangulEncodeBlock(uint16_t *encoded, const unsigned char *input, size_t len);

/// @}

#ifdef __cplusplus
}

template<Encoding encoding>
class BaseHangul {
public:
    static size_t Encode(unsigned char *encoded, const unsigned char *input, size_t len);
    static size_t Decode(unsigned char *decoded, const unsigned char *encoded, size_t len);
};
#endif

#endif //__BASE_HANGUL_H_
/// \endsection
