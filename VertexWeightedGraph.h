#include "IGraph.h"

class VertexWeightedGraph : public IGraph {
public:
  explicit VertexWeightedGraph(std::vector<Vertex> vertices, bool is_oriented);

  void AddEdge(size_t from, size_t to) final;

  size_t VerticesCount() const final;
  size_t EdgesCount() const final;
  bool IsOriented() const final;

  void GetNextVertices(size_t from, std::vector<Vertex> &vertices) const final;
  void GetPrevVertices(size_t to, std::vector<Vertex> &vertices) const final;

  void GetEdges(std::vector<Edge> &edges) const final;
  void GetVertices(std::vector<Vertex> &vertices) const final;

private:
  std::vector<Vertex> vertices_;
  std::vector<Edge> edges_;

  bool is_oriented_;
};
