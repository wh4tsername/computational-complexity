#pragma once

#ifndef IGRAPH_VERTEX_WEIGHTED_GRAPH
#define IGRAPH_VERTEX_WEIGHTED_GRAPH

#include "IGraph.h"

class VertexWeightedGraph : public IGraph {
public:
  explicit VertexWeightedGraph(std::vector<Vertex> vertices, bool is_oriented);
  ~VertexWeightedGraph() override = default;

  void AddEdge(size_t from, size_t to) final;

  size_t VerticesCount() const final;
  size_t EdgesCount() const final;
  bool IsOriented() const final;

  void GetNextVertices(size_t from, std::vector<Vertex> &vertices) const final;
  void GetPrevVertices(size_t to, std::vector<Vertex> &vertices) const final;

  void GetEdges(std::vector<Edge> &edges) const final;
  void GetVertices(std::vector<Vertex> &vertices) const final;

  void Print(std::ofstream &stream) const final;

protected:
  std::vector<Vertex> vertices_;
  std::vector<Edge> edges_;
  std::vector<Edge> distinct_edges_;

  bool is_oriented_;
};

#endif
