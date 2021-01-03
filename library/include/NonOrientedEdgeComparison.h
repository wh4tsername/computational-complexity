#pragma once

#include "VerticesComparison.h"

// non-oriented edge comparison
inline bool operator==(const Edge &lhs, const Edge &rhs) {
  return lhs.from_ == rhs.from_ && lhs.to_ == rhs.to_ ||
         lhs.from_ == rhs.to_ && lhs.to_ == rhs.from_;
}

struct edge_hash {
  inline std::size_t operator()(const Edge& obj) const {
    std::hash<size_t> hash;
    return hash(obj.from_.id_) ^ hash(obj.to_.id_);
  }
};
