set(TESTS_GEN_SOURCES main.cpp)

add_executable(tests_gen ${TESTS_GEN_SOURCES})

target_link_libraries(tests_gen PRIVATE IGraph)
