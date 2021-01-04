#include "Helpers.h"

bool get_ith_bit(size_t num, size_t i) { return (num >> i) & 1; }
void set_ith_bit(size_t &num, size_t i) { num |= (1 << i); }
