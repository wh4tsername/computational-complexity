#pragma once

#ifndef IGRAPH_HELPERS
#define IGRAPH_HELPERS

#include <unordered_set>
#include <vector>

#include "NonOrientedEdgeComparison.h"

#define ASSERT(condition, message)                                             \
  {                                                                            \
    if (condition) {                                                           \
      std::cerr << message << std::endl;                                       \
      exit(1);                                                                 \
    }                                                                          \
  }

#define PANIC(condition, message)                                              \
  {                                                                            \
    if (condition) {                                                           \
      throw std::runtime_error(message);                                       \
    }                                                                          \
  }

bool get_ith_bit(size_t num, size_t i);
void set_ith_bit(size_t &num, size_t i);

#endif
