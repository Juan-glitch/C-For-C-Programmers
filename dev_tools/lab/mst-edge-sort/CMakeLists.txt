cmake_minimum_required(VERSION 3.16)
project(MST_EDGE_SORT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ASSIGN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Module 4/Assignment4_MST")

set(COMMON_SOURCES
    "${ASSIGN_DIR}/Graph.cpp"
    "${ASSIGN_DIR}/utils/DisjointSet.cpp"
)

add_executable(mst-edge-sort main.cpp ${COMMON_SOURCES})
add_executable(mst-edge-sort_sort_order test/test_sort_order.cpp ${COMMON_SOURCES})
add_executable(mst-edge-sort_sort_preserves_edges test/test_sort_preserves_edges.cpp ${COMMON_SOURCES})
add_executable(mst-edge-sort_min_edge_first test/test_min_edge_first.cpp ${COMMON_SOURCES})

foreach(tgt mst-edge-sort mst-edge-sort_sort_order mst-edge-sort_sort_preserves_edges mst-edge-sort_min_edge_first)
    target_include_directories(${tgt} PRIVATE "${ASSIGN_DIR}")
endforeach()
