#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <utility>
#include "model/Edge.h"
#include "model/MSTResult.h"

class Graph {
public:
    Graph(int numberOfNodes);
    Graph(const std::string &filename);

    void addEdge(int from, int to, double weight);
    int getNodeCount() const;
    std::vector<Edge> getEdges() const;
    MSTResult minimumSpanningTree() const;

private:
    int nodeCount;
    std::vector<std::vector<std::pair<int, double>>> adjacencyList;
};

#endif
