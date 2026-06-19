#include <iostream>
#include "Graph.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Se requiere el nombre del fichero como argumento."
                  << std::endl;
        return 1;
    }

    try
    {
        Graph graph(argv[1]);

        MSTResult mst = graph.minimumSpanningTree();

        std::cout << "Minimum Spanning Tree" << std::endl;
        std::cout << std::endl;
        std::cout << "Total cost: " << mst.totalCost << std::endl;
        std::cout << std::endl;
        std::cout << "Edges:" << std::endl;
        for (const auto &edge : mst.edges)
        {
            std::cout << edge.from << " -- " << edge.to
                      << " : " << edge.weight << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
