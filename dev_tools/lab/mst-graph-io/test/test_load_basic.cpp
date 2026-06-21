#include <iostream>
#include <stdexcept>
#include "Graph.h"

int main()
{
    try {
        Graph g("data/mst_basic.txt");
        std::cout << "[OK] Loaded data/mst_basic.txt" << std::endl;
        std::cout << "Node count: " << g.getNodeCount() << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
