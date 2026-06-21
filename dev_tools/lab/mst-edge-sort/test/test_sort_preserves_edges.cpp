#include <iostream>
#include <algorithm>
#include <cassert>
#include "Graph.h"
#include "model/Edge.h"

int main()
{
    Graph g("data/mst_basic.txt");
    auto edges = g.getEdges();
    const size_t original_count = edges.size();

    std::sort(edges.begin(), edges.end(),
        [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

    assert(edges.size() == original_count);

    double total = 0.0;
    for (const auto &e : edges)
        total += e.weight;
    assert(total == 21.0);

    std::cout << "[OK] Sorting preserves edge count and total weight" << std::endl;
    return 0;
}
