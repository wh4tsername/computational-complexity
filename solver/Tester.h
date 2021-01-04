#pragma once

#include "CorrectnessChecker.h"
#include "MinVertexCoverSolver.h"

#include <Helpers.h>

#include <chrono>
#include <cmath>
#include <iomanip>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

void test(const IGraph &graph, std::ofstream &log_ostream,
          bool optimal_solver_off) {
  log_ostream << graph.VerticesCount() << "\t";
  log_ostream << graph.EdgesCount() << "\t";

  // time measurement
  auto start_tp = steady_clock::now();

  std::vector<Vertex> approx_vertex_cover =
      MinVertexCoverSolver::GetApproximation(graph);

  auto end_tp = steady_clock::now();
  double time = static_cast<double>(
                    duration_cast<microseconds>(end_tp - start_tp).count()) /
                1000;
  log_ostream << std::setprecision(3) << time << "\t";

  size_t approx_total = 0;
  for (Vertex vertex : approx_vertex_cover) {
    approx_total += vertex.weight_;
  }

  PANIC(!is_vertex_cover(graph, approx_vertex_cover),
        "Found set of vertices(approx) isn't a vertex cover!")

  log_ostream << approx_total;

  if (!optimal_solver_off) {
    log_ostream << "\t";

    std::vector<Vertex> optimal_vertex_cover =
        MinVertexCoverSolver::GetMinimum(graph);
    size_t optimal_total = 0;
    for (Vertex vertex : optimal_vertex_cover) {
      optimal_total += vertex.weight_;
    }

    log_ostream << optimal_total;

    PANIC(approx_total < optimal_total || approx_total > 2 * optimal_total,
          "Algorithm failure!")
  }
  log_ostream << std::endl;
}
