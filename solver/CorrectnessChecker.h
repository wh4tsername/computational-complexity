#pragma once

#include <Helpers.h>

bool is_vertex_cover(size_t bitmask, const std::vector<Vertex> &vertices,
                     const std::vector<Edge> &distinct_edges);

bool is_vertex_cover(const IGraph &graph,
                     const std::vector<Vertex> &vertex_cover);
