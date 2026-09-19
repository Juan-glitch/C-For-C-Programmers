#include <iostream>
#include "Graph.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <nombre_del_fichero>" << std::endl;
        return 1;
    }

    try
    {
        Graph graph(argv[1]);
        MSTResult mst = graph.minimumSpanningTree();

        std::cout << "Minimum Spanning Tree" << std::endl;
        std::cout << std::endl;
        for (size_t i = 0; i < mst.edges.size(); ++i)
        {
            const Edge &edge = mst.edges[i];
            std::cout << edge.from << " - " << edge.to
                      << " : " << edge.weight << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Total cost: " << mst.totalCost << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
