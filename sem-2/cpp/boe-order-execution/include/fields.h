#pragma once

#include "codec.h"

#include <algorithm>
#include <cmath>
#include <vector>

/*
 * Fields
 *  Account : Text(16)
 *  Capacity : Alpha(1)
 *  ClOrdID : Text(20)
 *  MaxFloor : Binary(4)
 *  OrderQty : Binary(4)
 *  OrdType : Alphanum(1)
 *  Price : BinaryPrice(8)
 *  Side : Alphanum(1)
 *  Symbol : Alphanum(8)
 *  TimeInForce : Alphanum(1)
 */
inline unsigned char * encode_text(unsigned char * start, const std::string & str, const size_t field_size)
{
    return encode(start, str, field_size);
}

inline unsigned char * encode_char(unsigned char * start, const char ch)
{
    return encode(start, static_cast<uint8_t>(ch));
}

inline unsigned char * encode_binary4(unsigned char * start, const uint32_t value)
{
    return encode(start, value);
}

inline unsigned char * encode_price(unsigned char * start, const double value)
{
    const double order = 10000;
    const double epsilon = 1e-5;
    // beware: no precision loss check
    return encode(start, static_cast<int64_t>(value * order + std::copysign(epsilon, value)));
}

inline constexpr size_t char_size = 1;
inline constexpr size_t binary4_size = 4;
inline constexpr size_t price_size = 8;
inline constexpr size_t order_fields_execuation_size = 70;
inline constexpr size_t optional_fields_execuation_size = 8;
inline constexpr size_t order_fields_restatement_size = 49;
inline constexpr size_t optional_fields_restatement_size = 6;

#define FIELD(name, protocol_type, ctype)                                                \
    inline unsigned char * encode_field_##name(unsigned char * start, const ctype value) \
    {                                                                                    \
        return encode_##protocol_type(start, value);                                     \
    }

#define VAR_FIELD(name, size)                                                                  \
    inline unsigned char * encode_field_##name(unsigned char * start, const std::string & str) \
    {                                                                                          \
        return encode_text(start, str, size);                                                  \
    }

#include "fields.inl"

#define FIELD(name, protocol_type, _) inline constexpr size_t name##_field_size = protocol_type##_size;
#define VAR_FIELD(name, size) inline constexpr size_t name##_field_size = size;

#include "fields.inl"

inline void set_opt_field_bit(unsigned char * bitfield_start, unsigned bitfield_num, unsigned bit)
{
    *(bitfield_start + bitfield_num - 1) |= bit;
}

inline std::string decode_fun_text(const std::vector<unsigned char> & message, const int offset, const int length)
{
    return std::string(message.begin() + offset, min(message.begin() + offset + length, std::find(message.begin() + offset, message.begin() + offset + length, '\0')));
}

inline int64_t decode_fun_binary(const std::vector<unsigned char> & message, const int offset, const int length)
{
    uint64_t result = 0;
    uint64_t deg = 1;
    for (int i = offset; i < offset + length; i++) {
        result += deg * message[i];
        deg *= 256;
    }
    return result;
}

inline double decode_fun_binary_price(const std::vector<unsigned char> & message, const int offset, const int length)
{
    double result = 0;
    uint64_t deg = 1;
    for (int i = offset; i < offset + length - 1; i++) {
        result += deg * message[i];
        deg *= 256;
    }
    result -= deg * message[offset + length - 1];
    return result / 1e4;
}
inline std::string decode_fun_binary_base36(const std::vector<unsigned char> & message, const int offset, int length)
{
    uint64_t result = decode_fun_binary(message, offset, length);
    std::vector<char> result_str;
    while (result > 0) {
        const int c = result % 36;
        result_str.push_back(c < 10 ? '0' + c : 'A' + c - 10);
        result /= 36;
    }
    return std::string(result_str.rbegin(), result_str.rend());
}

#define FIELD(name, type, offset, length)                                            \
    inline auto decode_execuation_##name(const std::vector<unsigned char> & message) \
    {                                                                                \
        return decode_fun_##type(message, offset, length);                           \
    }
#include "execuation_fields.inl"

#define FIELD(name, type, offset, length)                                             \
    inline auto decode_restatement_##name(const std::vector<unsigned char> & message) \
    {                                                                                 \
        return decode_fun_##type(message, offset, length);                            \
    }
#include "restatement_fields.inl"
