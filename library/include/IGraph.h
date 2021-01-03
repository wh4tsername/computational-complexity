#pragma once

#include <vector>
#include <fstream>

struct Vertex {
  Vertex(size_t id, int weight) : id_(id), weight_(weight) {}

  size_t id_;
  int weight_;
};

struct Edge {
  Edge(Vertex from, Vertex to) : from_(from), to_(to) {}

  Vertex from_;
  Vertex to_;
};

class IGraph {
public:
  virtual ~IGraph() = default;

  virtual void AddEdge(size_t from, size_t to) = 0;

  virtual size_t VerticesCount() const = 0;
  virtual size_t EdgesCount() const = 0;
  virtual bool IsOriented() const = 0;

  virtual void GetNextVertices(size_t from,
                               std::vector<Vertex> &vertices) const = 0;
  virtual void GetPrevVertices(size_t to,
                               std::vector<Vertex> &vertices) const = 0;

  virtual void GetEdges(std::vector<Edge> &edges) const = 0;
  virtual void GetVertices(std::vector<Vertex> &vertices) const = 0;

  virtual void Print(std::ofstream& stream) const = 0;
};
