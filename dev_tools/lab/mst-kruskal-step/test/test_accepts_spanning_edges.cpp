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
    int accepted = 0;
    for (const auto &e : edges) {
        if (ds.unite(e.from, e.to))
            ++accepted;
    }

    assert(accepted == g.getNodeCount() - 1);
    std::cout << "[OK] Kruskal accepted " << accepted << " spanning edges" << std::endl;
    return 0;
}
