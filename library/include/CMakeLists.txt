set(
        FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/IGraph.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VerticesComparison.h
        ${CMAKE_CURRENT_SOURCE_DIR}/NonOrientedEdgeComparison.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexWeightedGraph.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RandomVertexWeightedGraph.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers.h
)
set(SUBDIRECTORIES "")
set(RELATIVE_PATH include)

#Add all subdirectories
foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()

if(FILES)
    #Add source files to target
    target_sources(${LIBRARY_NAME} PRIVATE ${FILES})

    #Install our source files
    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
