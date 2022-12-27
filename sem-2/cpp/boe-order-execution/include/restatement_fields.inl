#ifndef FIELD
#error You need to define FIELD macro
#else
FIELD(cl_ord_id, text, 18, 20)
FIELD(active_volume, binary, order_fields_restatement_size + optional_fields_restatement_size, 4)
FIELD(secondary_order_id, binary_base36, order_fields_restatement_size + optional_fields_restatement_size + 4, 8)
#undef FIELD
#endif
