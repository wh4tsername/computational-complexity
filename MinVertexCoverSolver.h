#include "IGraph.h"

class MinVertexCoverSolver {
public:
  static std::vector<Vertex> GetApproximation(const IGraph &graph);
  static std::vector<Vertex> GetMinimum(const IGraph &graph);
};
