#pragma once

#ifndef IGRAPH_VERTICES_COMPARISON
#define IGRAPH_VERTICES_COMPARISON

#include "IGraph.h"

inline bool operator<(const Vertex &lhs, const Vertex &rhs) {
  return lhs.id_ < rhs.id_;
}

inline bool operator==(const Vertex &lhs, const Vertex &rhs) {
  return lhs.id_ == rhs.id_;
}

struct vertex_hash {
  inline std::size_t operator()(const Vertex& obj) const {
    std::hash<size_t> hash;
    return hash(obj.id_);
  }
};

#endif
