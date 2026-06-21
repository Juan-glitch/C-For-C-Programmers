cmake_minimum_required(VERSION 3.16)
project(MST_GRAPH_IO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ASSIGN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Module 4/Assignment4_MST")

set(COMMON_SOURCES
    "${ASSIGN_DIR}/Graph.cpp"
    "${ASSIGN_DIR}/utils/DisjointSet.cpp"
)

add_executable(mst-graph-io main.cpp ${COMMON_SOURCES})
add_executable(mst-graph-io_load_basic test/test_load_basic.cpp ${COMMON_SOURCES})
add_executable(mst-graph-io_node_count test/test_node_count.cpp ${COMMON_SOURCES})
add_executable(mst-graph-io_edge_count test/test_edge_count.cpp ${COMMON_SOURCES})

foreach(tgt mst-graph-io mst-graph-io_load_basic mst-graph-io_node_count mst-graph-io_edge_count)
    target_include_directories(${tgt} PRIVATE "${ASSIGN_DIR}")
endforeach()
