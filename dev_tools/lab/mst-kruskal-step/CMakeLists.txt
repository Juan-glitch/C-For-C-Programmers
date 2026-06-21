cmake_minimum_required(VERSION 3.16)
project(MST_KRUSKAL_STEP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ASSIGN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Module 4/Assignment4_MST")

set(COMMON_SOURCES
    "${ASSIGN_DIR}/Graph.cpp"
    "${ASSIGN_DIR}/utils/DisjointSet.cpp"
)

add_executable(mst-kruskal-step main.cpp ${COMMON_SOURCES})
add_executable(mst-kruskal-step_accepts_spanning_edges test/test_accepts_spanning_edges.cpp ${COMMON_SOURCES})
add_executable(mst-kruskal-step_skips_cycle_edges test/test_skips_cycle_edges.cpp ${COMMON_SOURCES})
add_executable(mst-kruskal-step_mst_cost test/test_mst_cost.cpp ${COMMON_SOURCES})

foreach(tgt mst-kruskal-step mst-kruskal-step_accepts_spanning_edges mst-kruskal-step_skips_cycle_edges mst-kruskal-step_mst_cost)
    target_include_directories(${tgt} PRIVATE "${ASSIGN_DIR}")
endforeach()
