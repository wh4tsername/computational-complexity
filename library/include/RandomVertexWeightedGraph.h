#pragma once

#ifndef IGRAPH_RANDOM_VERTEX_WEIGHTED_GRAPH
#define IGRAPH_RANDOM_VERTEX_WEIGHTED_GRAPH

#include <utility>

#include "VertexWeightedGraph.h"

class RandomVertexWeightedGraph : public VertexWeightedGraph {
public:
  explicit RandomVertexWeightedGraph(size_t num_vertices, double p,
                                     std::pair<size_t, size_t> weight_bounds,
                                     bool is_oriented);
};

#endif
