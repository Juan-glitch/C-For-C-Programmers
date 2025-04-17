#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <stdexcept>

class Graph
{
public:
    Graph();
    int addNode();
    void addEdge(int u, int v, double w);
    const std::vector<std::pair<int, double>> &neighbors(int u) const;
    int size() const;

private:
    std::vector<std::vector<std::pair<int, double>>> adj;
};

#endif //  GRAPH_H
