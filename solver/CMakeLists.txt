set(SOLVER_SOURCES main.cpp MinVertexCoverSolver.cpp CorrectnessChecker.cpp)

add_executable(test ${SOLVER_SOURCES})

target_link_libraries(test PRIVATE IGraph)
