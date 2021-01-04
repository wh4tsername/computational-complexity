#include <fstream>
#include <iostream>
#include <string>

#include <VertexWeightedGraph.h>

#include "Tester.h"

const size_t TEST_PRINT_FREQUENCY = 1;

int main(int argc, char **argv) {
  ASSERT(
      argc != 3 && argc != 4,
      "Pass test file path, log directory (and flag, if needed) as arguments!")

  std::string test_path(argv[1]);
  std::string log_dir(argv[2]);
  bool optimal_solver_off = false;
  if (argc == 4) {
    ASSERT(std::string(argv[3]) != "--optimal-off", "Unknown flag passed!")

    optimal_solver_off = true;
  }

  size_t slash_index = test_path.find_last_of('/');
  size_t dot_index = test_path.find_last_of('.');

  std::string name(test_path.substr(slash_index + 1, dot_index - slash_index - 1));

  std::ifstream test_istream(test_path);
  std::ofstream log_ostream(log_dir + name +".csv", std::ofstream::trunc);

  ASSERT(!test_istream.is_open(), "Can't open test file!")
  ASSERT(!log_ostream.is_open(), "Can't create " + name + ".csv in log directory!")

  // log header
  log_ostream << "|V|\t|E|\tapprox_time\tapprox";
  if (!optimal_solver_off) {
    log_ostream << "\toptimal_time\toptimal";
  }
  log_ostream << std::endl;

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

    test(graph, log_ostream, optimal_solver_off);

    if ((test_id + 1) % TEST_PRINT_FREQUENCY == 0 || test_id == num_tests - 1) {
      std::cerr << test_id + 1 << " tests passed!" << std::endl;
    }
  }

  return 0;
}
