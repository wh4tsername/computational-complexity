#pragma once

#include "CorrectnessChecker.h"
#include "MinVertexCoverSolver.h"

#include <Helpers.h>

void test(const IGraph &graph, std::ofstream &log_ostream,
          bool optimal_solver_off) {
  std::vector<Vertex> approx_vertex_cover =
      MinVertexCoverSolver::GetApproximation(graph);
  size_t approx_total = 0;
  for (Vertex vertex : approx_vertex_cover) {
    approx_total += vertex.weight_;
  }

  PANIC(!is_vertex_cover(graph, approx_vertex_cover),
      "Found set of vertices(approx) isn't a vertex cover!")

  log_ostream << approx_total << std::endl;

  if (!optimal_solver_off) {
    std::vector<Vertex> optimal_vertex_cover =
        MinVertexCoverSolver::GetMinimum(graph);
    size_t optimal_total = 0;
    for (Vertex vertex : optimal_vertex_cover) {
      optimal_total += vertex.weight_;
    }

    log_ostream << optimal_total << std::endl;

    PANIC(approx_total < optimal_total || approx_total > 2 * optimal_total,
          "Algorithm failure!")
  }
}
