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
    int skipped = 0;
    for (const auto &e : edges) {
        if (!ds.unite(e.from, e.to))
            ++skipped;
    }

    assert(skipped == static_cast<int>(edges.size()) - (g.getNodeCount() - 1));
    std::cout << "[OK] Kruskal skipped " << skipped << " cycle-forming edges" << std::endl;
    return 0;
}
