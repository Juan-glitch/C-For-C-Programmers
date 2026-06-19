#include <iostream>
#include <algorithm>
#include <iomanip>
#include "../Graph.h"
#include "../utils/DisjointSet.h"

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

        std::cout << "=== Kruskal step-by-step ===" << std::endl;
        std::cout << "Graph: " << filename << std::endl;
        std::cout << "Nodes: " << g.getNodeCount() << std::endl;
        std::cout << "Edges (sorted): " << edges.size() << std::endl;
        std::cout << "-----------------------------" << std::endl;

        for (size_t i = 0; i < edges.size(); ++i)
        {
            const auto &e = edges[i];
            std::cout << "[" << i << "]  " << e.from << " -- " << e.to
                      << "  w=" << std::setw(4) << e.weight;
        }
        std::cout << "\n-----------------------------" << std::endl;

        DisjointSet ds(g.getNodeCount());
        double total = 0.0;
        int accepted = 0;

        for (size_t i = 0; i < edges.size(); ++i)
        {
            const auto &e = edges[i];
            bool added = ds.unite(e.from, e.to);

            std::cout << "[" << i << "]  " << e.from << " -- " << e.to
                      << "  w=" << std::setw(4) << e.weight
                      << "  ->  " << (added ? "ACCEPTED" : "SKIP (cycle)")
                      << std::endl;

            if (added)
            {
                total += e.weight;
                ++accepted;
            }
        }

        std::cout << "-----------------------------" << std::endl;
        std::cout << "MST edges: " << accepted << " / " << edges.size() << std::endl;
        std::cout << "Total cost: " << total << std::endl;
        std::cout << "Expected:   " << (g.getNodeCount() - 1)
                  << " edges for a spanning tree" << std::endl;

        if (accepted == g.getNodeCount() - 1)
            std::cout << "[OK] Valid spanning tree" << std::endl;
        else
            std::cout << "[FAIL] Wrong edge count" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
