#include <iostream>
#include <cassert>
#include "Graph.h"

int main()
{
    Graph g("data/mst_basic.txt");
    assert(g.getNodeCount() == 4);
    std::cout << "[OK] Node count is 4" << std::endl;
    return 0;
}
