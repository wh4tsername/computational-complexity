#include "MinVertexCoverSolver.h"

#include <cstdint>
#include <unordered_set>

#include <Helpers.h>
#include <NonOrientedEdgeComparison.h>

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

bool is_vertex_cover(size_t bitmask, const std::vector<Vertex> &vertices,
                     const std::vector<Edge> &distinct_edges) {
  std::vector<bool> edge_mask(distinct_edges.size(), false);
  for (size_t i = 0; i < vertices.size(); ++i) {
    if (get_ith_bit(bitmask, i)) {
      for (size_t edge_id = 0; edge_id < distinct_edges.size(); ++edge_id) {
        if (!edge_mask[edge_id] &&
            (distinct_edges[edge_id].from_ == vertices[i] ||
             distinct_edges[edge_id].to_ == vertices[i])) {
          edge_mask[edge_id] = true;
        }
      }
    }
  }

  bool flag = true;
  for (auto &&bit : edge_mask) {
    if (!bit) {
      flag = false;
      break;
    }
  }

  return flag;
}

std::vector<Vertex> MinVertexCoverSolver::GetMinimum(const IGraph &graph) {
  std::vector<Vertex> vertices;
  graph.GetVertices(vertices);

  std::vector<Edge> edges;
  graph.GetEdges(edges);
  get_distinct_edges(edges);

  size_t min_weight = UINT32_MAX;
  size_t cover_mask = 0;
  for (size_t bitmask = 0; bitmask < (1 << graph.VerticesCount()); ++bitmask) {
    if (is_vertex_cover(bitmask, vertices, edges)) {
      size_t total = 0;

      for (size_t i = 0; i < graph.VerticesCount(); ++i) {
        if (get_ith_bit(bitmask, i)) {
          total += vertices[i].weight_;
        }
      }

      if (total < min_weight) {
        min_weight = total;
        cover_mask = bitmask;
      }
    }
  }

  std::vector<Vertex> vertex_cover;
  for (size_t i = 0; i < graph.VerticesCount(); ++i) {
    if (get_ith_bit(cover_mask, i)) {
      vertex_cover.emplace_back(vertices[i]);
    }
  }

  return vertex_cover;
}

std::vector<Vertex>
MinVertexCoverSolver::GetApproximation(const IGraph &graph) {
  std::vector<Vertex> vertices;
  graph.GetVertices(vertices);

  std::vector<Edge> edges;
  graph.GetEdges(edges);
  get_distinct_edges(edges);

  std::vector<int> remaining_weights(graph.VerticesCount());
  for (auto &&vertex : vertices) {
    remaining_weights[vertex.id_] = vertex.weight_;
  }

  std::unordered_set<Vertex, vertex_hash> vertex_cover;

  std::vector<size_t> prices(graph.EdgesCount());
  for (size_t edge_id = 0; edge_id < edges.size(); ++edge_id) {
    Edge &edge = edges[edge_id];
    Vertex &from = edge.from_;
    Vertex &to = edge.to_;

    if (remaining_weights[from.id_] == 0 || remaining_weights[to.id_] == 0) {
      if (remaining_weights[from.id_] == 0) {
        vertex_cover.insert(from);
      }
      if (remaining_weights[to.id_] == 0) {
        vertex_cover.insert(to);
      }

      continue;
    }

    bool flag = remaining_weights[from.id_] < remaining_weights[to.id_];
    Vertex &smaller = flag ? from : to;
    Vertex &bigger = flag ? to : from;

    size_t smaller_weight = remaining_weights[smaller.id_];
    prices[edge_id] = smaller_weight;

    remaining_weights[smaller.id_] -= smaller_weight;
    remaining_weights[bigger.id_] -= smaller_weight;

    vertex_cover.insert(smaller);
    if (remaining_weights[bigger.id_] == 0) {
      vertex_cover.insert(bigger);
    }
  }

  size_t mask = 0;
  std::vector<Vertex> vertex_cover_vector(vertex_cover.size());
  for (auto &&vertex : vertex_cover) {
    set_ith_bit(mask, vertex.id_);
    vertex_cover_vector.emplace_back(vertex);
  }

  PANIC(!is_vertex_cover(mask, vertices, edges),
        "Found set of vertices isn't a vertex cover!")

  return vertex_cover_vector;
}
