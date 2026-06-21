#include <iostream>
#include <algorithm>
#include <cassert>
#include "Graph.h"
#include "utils/DisjointSet.h"

int main()
{
    Graph g("data/mst_basic.txt");
    auto edges = g.getEdges();

    std::sort(edges.begin(), edges.end(),
        [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

    DisjointSet ds(g.getNodeCount());
    double total = 0.0;
    for (const auto &e : edges) {
        if (ds.unite(e.from, e.to))
            total += e.weight;
    }

    assert(total == 1.0 + 2.0 + 3.0);
    std::cout << "[OK] MST total cost is " << total << std::endl;
    return 0;
}
