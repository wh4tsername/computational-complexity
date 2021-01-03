#include <RandomVertexWeightedGraph.h>

int main(int argc, char **argv) {
  std::string output_path(argv[1]);
  std::ofstream ostream(output_path, std::ofstream::trunc);

  RandomVertexWeightedGraph graph(3, 0.5, {0, 5}, false);

  graph.Print(ostream);

  return 0;
}
