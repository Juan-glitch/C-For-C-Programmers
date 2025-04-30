#include "Graph.h"
#include "GraphGenerator.h"
#include "GraphUtils.h"

/**
 * Main function.
 *
 * @return 0 on success.
 */
int main()
{
    // Parameters for the random graph
    int N = 3; // Number of nodes
    double density = 0.2, w_min = 1.0, w_max = 10.0;

    // Generate a random graph
    Graph g = generateRandomGraph(N, density, w_min, w_max);

    // Print the graph
    printGraph(g);
    return 0;
}