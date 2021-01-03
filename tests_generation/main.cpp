#include <RandomVertexWeightedGraph.h>

int main(int argc, char **argv) {
  std::string output_path(argv[1]);
  std::ofstream ostream(output_path, std::ofstream::trunc);

  size_t num_tests = 10000;
  ostream << num_tests << std::endl << std::endl;

  for (size_t i = 0; i < num_tests; ++i) {
    RandomVertexWeightedGraph graph(7, 0.5, {0, 1000}, false);

    graph.Print(ostream);
    ostream << std::endl;
  }

  return 0;
}
