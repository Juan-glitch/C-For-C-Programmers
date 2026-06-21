#include <iostream>
#include <algorithm>
#include <cassert>
#include "Graph.h"
#include "model/Edge.h"

int main()
{
    Graph g("data/mst_basic.txt");
    auto edges = g.getEdges();

    std::sort(edges.begin(), edges.end(),
        [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

    assert(edges.front().weight == 1.0);
    assert(edges.front().from == 0);
    assert(edges.front().to == 1);

    std::cout << "[OK] Minimum edge (0--1, weight 1) is first after sorting" << std::endl;
    return 0;
}
