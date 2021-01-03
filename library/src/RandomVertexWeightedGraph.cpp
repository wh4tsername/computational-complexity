#include "RandomVertexWeightedGraph.h"

#include <random>

RandomVertexWeightedGraph::RandomVertexWeightedGraph(
    size_t num_vertices, double p,
    std::pair<size_t, size_t> weight_bounds, bool is_oriented)
    : VertexWeightedGraph({}, is_oriented) {
  std::random_device dev;
  std::mt19937 rng(dev());

  std::uniform_int_distribution<std::mt19937::result_type> weight_dist(
      weight_bounds.first, weight_bounds.second);

  for (size_t vertex_id = 0; vertex_id < num_vertices; ++vertex_id) {
    vertices_.emplace_back(vertex_id, weight_dist(rng));
  }

  std::bernoulli_distribution edge_indicator(p);
  for (size_t from = 0; from < num_vertices; ++from) {
    for (size_t to = IsOriented() ? 0 : from + 1; to < num_vertices; ++to) {
      if (from != to && edge_indicator(rng)) {
        AddEdge(from, to);
      }
    }
  }
}
