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

    assert(edges.size() == 6);
    assert(edges[0].weight == 1.0);
    assert(edges[1].weight == 2.0);
    assert(edges[2].weight == 3.0);
    assert(edges[3].weight == 4.0);
    assert(edges[4].weight == 5.0);
    assert(edges[5].weight == 6.0);

    std::cout << "[OK] Edges sorted ascending by weight" << std::endl;
    return 0;
}
