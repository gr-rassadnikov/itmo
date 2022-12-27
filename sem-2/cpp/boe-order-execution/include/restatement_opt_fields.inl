#ifndef FIELD
#error You need to define FIELD macro
#else
FIELD(active_volume, 5, 2)
FIELD(secondary_order_id, 6, 1)
#undef FIELD
#endif
