#include <RandomVertexWeightedGraph.h>

#include <iostream>

int main(int argc, char **argv) {
  std::string output_path(argv[1]);
  std::ofstream ostream(output_path, std::ofstream::trunc);

  size_t num_tests = 100;
  ostream << num_tests << std::endl << std::endl;

  for (size_t i = 0; i < num_tests; ++i) {
    RandomVertexWeightedGraph graph(100, 1, {0, 1000}, false);

    graph.Print(ostream);
    ostream << std::endl;

    if ((i + 1) % 10 == 0 || i == num_tests - 1) {
      std::cerr << i + 1 << " graphs generated!" << std::endl;
    }
  }

  return 0;
}
