#include "Graph.h"
#include "GraphUtils.h"
#include <iostream>
using namespace std;

/**
 * Prints the adjacency list of a graph.
 *
 * @param g The graph to print.
 */
void printGraph(const Graph &g)
{
    // Iterate over each node in the graph
    for (int u = 0; u < g.size(); ++u)
    {
        cout << u << ": ";
        // Iterate over each neighbor of the node
        for (const auto [node, edge] : g.neighbors(u))
        {
            cout << "(" << node << ", " << edge << ") ";
        }
        cout << '\n';
    }
}
