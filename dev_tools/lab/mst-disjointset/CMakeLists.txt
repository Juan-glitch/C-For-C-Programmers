cmake_minimum_required(VERSION 3.16)
project(MST_DISJOINTSET LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ASSIGN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Module 4/Assignment4_MST")

set(COMMON_SOURCES "${ASSIGN_DIR}/utils/DisjointSet.cpp")

add_executable(mst-disjointset main.cpp ${COMMON_SOURCES})
add_executable(mst-disjointset_union_basics test/test_union_basics.cpp ${COMMON_SOURCES})
add_executable(mst-disjointset_cycle_detection test/test_cycle_detection.cpp ${COMMON_SOURCES})
add_executable(mst-disjointset_component_merge test/test_component_merge.cpp ${COMMON_SOURCES})

foreach(tgt mst-disjointset mst-disjointset_union_basics mst-disjointset_cycle_detection mst-disjointset_component_merge)
    target_include_directories(${tgt} PRIVATE "${ASSIGN_DIR}")
endforeach()
