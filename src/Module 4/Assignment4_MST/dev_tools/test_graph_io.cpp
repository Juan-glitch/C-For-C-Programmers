#include <iostream>
#include "../Graph.h"

int main(int argc, char *argv[])
{
    const char *filename = (argc >= 2)
        ? argv[1]
        : "../test_data/mst_basic.txt";

    try
    {
        Graph g(filename);
        std::cout << "File: " << filename << std::endl;
        std::cout << "Node count: " << g.getNodeCount() << std::endl;
        std::cout << "Edges read:" << std::endl;

        for (const auto &e : g.getEdges())
        {
            std::cout << "  " << e.from << " -- " << e.to
                      << " : " << e.weight << std::endl;
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
