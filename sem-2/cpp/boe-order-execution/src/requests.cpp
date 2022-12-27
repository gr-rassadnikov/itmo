#include "requests.h"

namespace {

void encode_new_order_opt_fields(unsigned char * bitfield_start,
                                 const double price,
                                 const char ord_type,
                                 const char time_in_force,
                                 const unsigned max_floor,
                                 const std::string & symbol,
                                 const char capacity,
                                 const std::string & account)
{
    auto * p = bitfield_start + new_order_bitfield_num();
#define FIELD(name, bitfield_num, bit)                    \
    set_opt_field_bit(bitfield_start, bitfield_num, bit); \
    p = encode_field_##name(p, name);
#include "new_order_opt_fields.inl"
}

uint8_t encode_request_type(const RequestType type)
{
    switch (type) {
    case RequestType::New:
        return 0x38;
    }
    return 0;
}

unsigned char * add_request_header(unsigned char * start, unsigned length, const RequestType type, unsigned seq_no)
{
    *start++ = 0xBA;
    *start++ = 0xBA;
    start = encode(start, static_cast<uint16_t>(length));
    start = encode(start, encode_request_type(type));
    *start++ = 0;
    return encode(start, seq_no);
}

char convert_side(const Side side)
{
    switch (side) {
    case Side::Buy: return '1';
    case Side::Sell: return '2';
    }
    return 0;
}

char convert_ord_type(const OrdType ord_type)
{
    switch (ord_type) {
    case OrdType::Market: return '1';
    case OrdType::Limit: return '2';
    case OrdType::Pegged: return 'P';
    }
    return 0;
}

char convert_time_in_force(const TimeInForce time_in_force)
{
    switch (time_in_force) {
    case TimeInForce::Day: return '0';
    case TimeInForce::IOC: return '3';
    case TimeInForce::GTD: return '6';
    }
    return 0;
}

char convert_capacity(const Capacity capacity)
{
    switch (capacity) {
    case Capacity::Agency: return 'A';
    case Capacity::Principal: return 'P';
    case Capacity::RisklessPrincipal: return 'R';
    }
    return 0;
}

} // anonymous namespace

std::array<unsigned char, calculate_size(RequestType::New)> create_new_order_request(const unsigned seq_no,
                                                                                     const std::string & cl_ord_id,
                                                                                     const Side side,
                                                                                     const double volume,
                                                                                     const double price,
                                                                                     const OrdType ord_type,
                                                                                     const TimeInForce time_in_force,
                                                                                     const double max_floor,
                                                                                     const std::string & symbol,
                                                                                     const Capacity capacity,
                                                                                     const std::string & account)
{
    static_assert(calculate_size(RequestType::New) == 78, "Wrong New Order message size");

    std::array<unsigned char, calculate_size(RequestType::New)> msg;
    auto * p = add_request_header(&msg[0], msg.size() - 2, RequestType::New, seq_no);
    p = encode_text(p, cl_ord_id, 20);
    p = encode_char(p, convert_side(side));
    p = encode_binary4(p, static_cast<uint32_t>(volume));
    p = encode(p, static_cast<uint8_t>(new_order_bitfield_num()));
    encode_new_order_opt_fields(p,
                                price,
                                convert_ord_type(ord_type),
                                convert_time_in_force(time_in_force),
                                max_floor,
                                symbol,
                                convert_capacity(capacity),
                                account);
    return msg;
}

LiquidityIndicator decode_liquidity_indicator(const std::vector<unsigned char> & message, const int offset)
{
    const unsigned char c = message[offset];
    switch (c) {
    case 'A':
        return LiquidityIndicator::Added;

    case 'R':
        return LiquidityIndicator::Removed;
    }
    return LiquidityIndicator::Unknown;
}

RestatementReason decode_type_alphanumeric_reason(const std::vector<unsigned char> & message, const int offset)
{
    const unsigned char c = message[offset];
    switch (c) {
    case 'R':
        return RestatementReason::Reroute;
    case 'X':
        return RestatementReason::LockedInCross;
    case 'W':
        return RestatementReason::Wash;
    case 'L':
        return RestatementReason::Reload;
    case 'Q':
        return RestatementReason::LiquidityUpdated;
    }
    return RestatementReason::Unknown;
}

ExecutionDetails decode_order_execution(const std::vector<unsigned char> & message)
{
    ExecutionDetails exec_details;
#define FIELD(name, _, __, ___) \
    exec_details.name = decode_execuation_##name(message);
    exec_details.liquidity_indicator = decode_liquidity_indicator(message, 62);
#include "execuation_fields.inl"

    return exec_details;
}

RestatementDetails decode_order_restatement(const std::vector<unsigned char> & message)
{
    RestatementDetails restatement_details;
#define FIELD(name, _, __, ___) \
    restatement_details.name = decode_restatement_##name(message);
    restatement_details.reason = decode_type_alphanumeric_reason(message, 46);
#include "restatement_fields.inl"
    return restatement_details;
}

std::vector<unsigned char> request_optional_fields_for_message(const ResponseType response_type)
{
    std::vector<unsigned char> bits_fields;
    switch (response_type) {
    case (ResponseType::OrderExecution):
        bits_fields = std::vector<unsigned char>(
                std::max({0
#define FIELD(_, bitfield_num, __) , bitfield_num
#include "execution_opt_fields.inl"
                }),
                0);
#define FIELD(_, bitfield_num, bit) \
    bits_fields[bitfield_num - 1] |= bit;
#include "execution_opt_fields.inl"
        break;
    case (ResponseType::OrderRestatement):
        bits_fields = std::vector<unsigned char>(
                std::max({0
#define FIELD(_, bitfield_num, __) , bitfield_num
#include "restatement_opt_fields.inl"
                }),
                0);
#define FIELD(_, bitfield_num, bit) \
    bits_fields[bitfield_num - 1] |= bit;
#include "restatement_opt_fields.inl"
        break;
    default:
        break;
    }
    return bits_fields;
}
