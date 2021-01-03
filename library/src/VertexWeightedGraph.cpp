#include "../include/VertexWeightedGraph.h"

#include <algorithm>

VertexWeightedGraph::VertexWeightedGraph(std::vector<Vertex> vertices,
                                         bool is_oriented)
    : vertices_(std::move(vertices)), is_oriented_(is_oriented) {
  std::sort(vertices_.begin(), vertices_.end());
}

void VertexWeightedGraph::AddEdge(size_t from, size_t to) {
  edges_.emplace_back(vertices_[from], vertices_[to]);
  if (!is_oriented_) {
    edges_.emplace_back(vertices_[to], vertices_[from]);
  }
}

size_t VertexWeightedGraph::VerticesCount() const { return vertices_.size(); }

size_t VertexWeightedGraph::EdgesCount() const { return edges_.size(); }

bool VertexWeightedGraph::IsOriented() const { return is_oriented_; }

void VertexWeightedGraph::GetNextVertices(size_t from,
                                          std::vector<Vertex> &vertices) const {
  vertices.clear();

  for (auto &&edge : edges_) {
    if (edge.from_.id_ == from) {
      vertices.emplace_back(edge.to_);
    }
  }
}

void VertexWeightedGraph::GetPrevVertices(size_t to,
                                          std::vector<Vertex> &vertices) const {
  vertices.clear();

  for (auto &&edge : edges_) {
    if (edge.to_.id_ == to) {
      vertices.emplace_back(edge.from_);
    }
  }
}

void VertexWeightedGraph::GetEdges(std::vector<Edge> &edges) const {
  edges.clear();

  edges = edges_;
}

void VertexWeightedGraph::GetVertices(std::vector<Vertex> &vertices) const {
  vertices.clear();

  vertices = vertices_;
}
