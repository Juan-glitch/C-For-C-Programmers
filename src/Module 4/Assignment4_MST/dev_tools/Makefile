CXX := g++
CXXFLAGS := -std=c++17 -Wall -g -O0 -I..
SRC_DIR := ..

.PHONY: all clean test_disjointset test_graph_io test_edge_sort test_kruskal_step

all: test_disjointset test_graph_io test_edge_sort test_kruskal_step

test_disjointset: test_disjointset.cpp $(SRC_DIR)/utils/DisjointSet.cpp
	$(CXX) $(CXXFLAGS) test_disjointset.cpp $(SRC_DIR)/utils/DisjointSet.cpp -o test_disjointset

test_graph_io: test_graph_io.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/utils/DisjointSet.cpp
	$(CXX) $(CXXFLAGS) test_graph_io.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/utils/DisjointSet.cpp -o test_graph_io

test_edge_sort: test_edge_sort.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/utils/DisjointSet.cpp
	$(CXX) $(CXXFLAGS) test_edge_sort.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/utils/DisjointSet.cpp -o test_edge_sort

test_kruskal_step: test_kruskal_step.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/utils/DisjointSet.cpp
	$(CXX) $(CXXFLAGS) test_kruskal_step.cpp $(SRC_DIR)/Graph.cpp $(SRC_DIR)/utils/DisjointSet.cpp -o test_kruskal_step

clean:
	rm -f test_disjointset test_graph_io test_edge_sort test_kruskal_step
