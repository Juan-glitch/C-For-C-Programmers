#include <iostream>
#include <cassert>
#include "Graph.h"

int main()
{
    Graph g("data/mst_basic.txt");
    auto edges = g.getEdges();
    assert(edges.size() == 6);

    double total = 0.0;
    for (const auto &e : edges)
        total += e.weight;
    assert(total == 1.0 + 2.0 + 3.0 + 4.0 + 5.0 + 6.0);

    std::cout << "[OK] Edge count is 6 and total weight is 21" << std::endl;
    return 0;
}
