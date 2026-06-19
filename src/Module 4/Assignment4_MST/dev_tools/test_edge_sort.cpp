#include <iostream>
#include <algorithm>
#include <vector>
#include "../Graph.h"
#include "../model/Edge.h"

int main(int argc, char *argv[])
{
    const char *filename = (argc >= 2)
        ? argv[1]
        : "../test_data/mst_basic.txt";

    try
    {
        Graph g(filename);
        auto edges = g.getEdges();

        std::sort(edges.begin(), edges.end(),
            [](const Edge &a, const Edge &b) {
                return a.weight < b.weight;
            });

        std::cout << "Edges sorted by weight (" << filename << "):" << std::endl;
        for (const auto &e : edges)
        {
            std::cout << "  " << e.from << " -- " << e.to
                      << "  weight=" << e.weight << std::endl;
        }

        std::cout << "\nTotal edges: " << edges.size() << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
