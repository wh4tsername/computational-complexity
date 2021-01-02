cmake_minimum_required(VERSION 3.17)
project(computational_complexity)

set(CMAKE_CXX_STANDARD 17)

add_executable(computational_complexity main.cpp VertexWeightedGraph.cpp MinVertexCoverSolver.cpp)
