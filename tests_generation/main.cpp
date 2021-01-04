#include <Helpers.h>
#include <RandomVertexWeightedGraph.h>

#include <iostream>
#include <random>

enum class TEST_CASE { None = 0, Random, Corner };

const size_t TEST_PRINT_FREQUENCY = 1;

void corner_test(std::ofstream &ostream, size_t num_tests) {
  ostream << num_tests << std::endl << std::endl;

  std::random_device dev;
  std::mt19937 rng(dev());

  for (size_t i = 0; i < num_tests; ++i) {
    size_t num_vertices = i + 2;

    std::vector<Vertex> vertices;
    for (size_t vertex_id = 0; vertex_id < num_vertices; ++vertex_id) {
      vertices.emplace_back(vertex_id, 1);
    }

    VertexWeightedGraph graph(vertices, false);

    for (size_t from = 0; from < num_vertices - 1; ++from) {
      graph.AddEdge(from, from + 1);
    }

    graph.Print(ostream);
    ostream << std::endl;

    if ((i + 1) % TEST_PRINT_FREQUENCY == 0 || i == num_tests - 1) {
      std::cerr << i + 1 << " graphs generated!" << std::endl;
    }
  }
}

void random_test(std::ofstream &ostream, size_t num_tests) {
  ostream << num_tests << std::endl << std::endl;

  for (size_t i = 0; i < num_tests; ++i) {
    RandomVertexWeightedGraph graph(500, 0.5, {0, 1000}, false);

    graph.Print(ostream);
    ostream << std::endl;

    if ((i + 1) % TEST_PRINT_FREQUENCY == 0 || i == num_tests - 1) {
      std::cerr << i + 1 << " graphs generated!" << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  std::string output_path(argv[1]);
  std::ofstream ostream(output_path, std::ofstream::trunc);

  size_t num_tests = std::stoi(std::string(argv[2]));

  std::string flag_str(argv[3]);
  TEST_CASE test_case = TEST_CASE::None;
  if (flag_str == "--random") {
    test_case = TEST_CASE::Random;
  } else if (flag_str == "--corner") {
    test_case = TEST_CASE::Corner;
  } else {
    ASSERT(true, "Unknown flag!");
  }

  switch (test_case) {
  case TEST_CASE::Random:
    random_test(ostream, num_tests);
    break;
  case TEST_CASE::Corner:
    corner_test(ostream, num_tests);
    break;
  case TEST_CASE::None:
    break;
  }

  return 0;
}
