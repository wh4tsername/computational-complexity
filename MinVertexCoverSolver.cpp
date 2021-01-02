#include "MinVertexCoverSolver.h"

#include <cstdint>

std::vector<Vertex>
MinVertexCoverSolver::GetApproximation(const IGraph &graph) {
  std::vector<Vertex> vertices;
  graph.GetVertices(vertices);

  std::vector<Edge> edges;
  graph.GetEdges(edges);

  std::vector<int> remaining_weights(graph.VerticesCount());
  for (auto &&vertex : vertices) {
    remaining_weights[vertex.id_] = vertex.weight_;
  }

  std::vector<Vertex> vertex_cover;

  std::vector<size_t> prices(graph.EdgesCount());
  for (size_t edge_id = 0; edge_id < edges.size(); ++edge_id) {
    Edge &edge = edges[edge_id];
    Vertex &from = edge.from_;
    Vertex &to = edge.to_;

    if (remaining_weights[from.id_] == 0 || remaining_weights[to.id_] == 0) {
      continue;
    }

    bool flag = remaining_weights[from.id_] < remaining_weights[to.id_];
    Vertex &smaller = flag ? from : to;
    Vertex &bigger = flag ? to : from;

    size_t smaller_weight = remaining_weights[smaller.id_];
    prices[edge_id] = smaller_weight;

    remaining_weights[smaller.id_] -= smaller_weight;
    remaining_weights[bigger.id_] -= smaller_weight;

    vertex_cover.emplace_back(smaller);
  }

  return vertex_cover;
}

bool get_ith_bit(size_t num, size_t i) { return (num >> i) & 1; }

bool is_vertex_cover(size_t bitmask, const std::vector<Vertex> &vertices,
                     const std::vector<Edge> &edges) {
  std::vector<bool> edge_mask(edges.size(), false);
  for (size_t i = 0; i < vertices.size(); ++i) {
    if (get_ith_bit(bitmask, i)) {
      for (size_t edge_id = 0; edge_id < edges.size(); ++edge_id) {
        if (!edge_mask[edge_id] && (edges[edge_id].from_ == vertices[i] ||
                                    edges[edge_id].to_ == vertices[i])) {
          edge_mask[edge_id] = true;
        }
      }
    }
  }

  bool flag = true;
  for (auto &&bit : edge_mask) {
    if (!bit) {
      flag = false;
    }
  }

  return flag;
}

std::vector<Vertex> MinVertexCoverSolver::GetMinimum(const IGraph &graph) {
  std::vector<Vertex> vertices;
  graph.GetVertices(vertices);

  std::vector<Edge> edges;
  graph.GetEdges(edges);

  size_t min_weight = UINT32_MAX;
  size_t cover_mask = 0;
  for (size_t bitmask = 1; bitmask < (1 << graph.VerticesCount()); ++bitmask) {
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
