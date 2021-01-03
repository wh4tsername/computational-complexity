#include "Helpers.h"

bool get_ith_bit(size_t num, size_t i) { return (num >> i) & 1; }
void set_ith_bit(size_t &num, size_t i) { num |= (1 << i); }

void get_distinct_edges(std::vector<Edge> &edges) {
  std::unordered_set<Edge, edge_hash> distinct_edges_set;
  for (Edge edge : edges) {
    distinct_edges_set.insert(edge);
  }

  edges.clear();
  for (auto [from, to] : distinct_edges_set) {
    edges.emplace_back(from, to);
  }
}
