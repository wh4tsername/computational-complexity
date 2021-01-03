#include <fstream>
#include <iostream>
#include <string>

#include <VertexWeightedGraph.h>
#include "MinVertexCoverSolver.h"

#define ASSERT(condition, message)                                             \
  {                                                                            \
    if (condition) {                                                           \
      std::cerr << message << std::endl;                                       \
      exit(1);                                                                 \
    }                                                                          \
  }

void test(const IGraph &graph, std::ofstream &log_ostream) {
  std::vector<Vertex> approx_vertex_cover =
      MinVertexCoverSolver::GetApproximation(graph);
  size_t approx_total = 0;
  for (Vertex vertex : approx_vertex_cover) {
    approx_total += vertex.weight_;
  }

  log_ostream << approx_total << std::endl;

  std::vector<Vertex> optimal_vertex_cover =
      MinVertexCoverSolver::GetMinimum(graph);
  size_t optimal_total = 0;
  for (Vertex vertex : optimal_vertex_cover) {
    optimal_total += vertex.weight_;
  }

  log_ostream << optimal_total << std::endl;
}

int main(int argc, char **argv) {
  ASSERT(argc != 3, "Pass test file path and log directory as arguments!")

  std::string test_path(argv[1]);
  std::string log_dir(argv[2]);

  std::ifstream test_istream(test_path);
  std::ofstream log_ostream(log_dir + "log.txt", std::ofstream::trunc);

  ASSERT(!test_istream.is_open(), "Can't open test file!")
  ASSERT(!log_ostream.is_open(), "Can't create log.txt in log directory!")

  size_t num_tests = 0;
  test_istream >> num_tests;

  for (size_t test_id = 0; test_id < num_tests; ++test_id) {
    size_t num_vertices = 0;
    size_t num_edges = 0;

    test_istream >> num_vertices >> num_edges;

    std::vector<Vertex> vertices;
    for (size_t vertex_id = 0; vertex_id < num_vertices; ++vertex_id) {
      int weight = 0;
      test_istream >> weight;

      vertices.emplace_back(vertex_id, weight);
    }

    std::vector<std::pair<size_t, size_t>> edges(num_edges);
    for (size_t edge_id = 0; edge_id < num_edges; ++edge_id) {
      test_istream >> edges[edge_id].first >> edges[edge_id].second;
    }

    VertexWeightedGraph graph(vertices, false);
    for (auto [from_id, to_id] : edges) {
      graph.AddEdge(from_id, to_id);
    }

    test(graph, log_ostream);

    if (test_id != num_tests - 1) {
      log_ostream << std::endl;
    }
  }

  return 0;
}
