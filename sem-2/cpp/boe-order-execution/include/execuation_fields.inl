#ifndef FIELD
#error You need to define FIELD macro
#else
FIELD(cl_ord_id, text, 18, 20)
FIELD(exec_id, binary_base36, 38, 8)
FIELD(filled_volume, binary, 46, 4)
FIELD(price, binary_price, 50, 8)
FIELD(active_volume, binary, 58, 4)
FIELD(symbol, text, optional_fields_execuation_size + order_fields_execuation_size, 8)
FIELD(last_mkt, text, optional_fields_execuation_size + order_fields_execuation_size + 8, 4)
FIELD(fee_code, text, optional_fields_execuation_size + order_fields_execuation_size + 12, 2)
#undef FIELD
#endif
