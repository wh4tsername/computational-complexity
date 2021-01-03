set(
        LIBRARY_SOURCES
        include/IGraph.h
        include/VertexWeightedGraph.h
        src/VertexWeightedGraph.cpp
)
set(LIBRARY_NAME IGraph)

option(BUILD_SHARED_LIBS True)

add_library(${LIBRARY_NAME})

target_include_directories(
        ${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> #export.h
        $<INSTALL_INTERFACE:include> #${CMAKE_INSTALL_PREFIX}/include
)

include(GenerateExportHeader)
generate_export_header(${LIBRARY_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/export.h DESTINATION include)

add_subdirectory(include)
add_subdirectory(src)
