#include "CorrectnessChecker.h"

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

bool is_vertex_cover(const IGraph &graph,
                     const std::vector<Vertex> &vertex_cover) {
  std::vector<Vertex> vertices;
  graph.GetVertices(vertices);

  std::vector<Edge> edges;
  graph.GetEdges(edges);
  get_distinct_edges(edges);

  size_t bitmask = 0;
  for (Vertex vertex : vertex_cover) {
    set_ith_bit(bitmask, vertex.id_);
  }

  return is_vertex_cover(bitmask, vertices, edges);
}
