#include "GraphGenerator.h"
#include <random>
#include <iostream>
#include <stdexcept>
#include "Graph.h"

using namespace std;

using GraphEngine = std::mt19937;
using RealDist = std::uniform_real_distribution<double>;

/**
 * Generates a random graph with N nodes, edge density, and weight range.
 *
 * @param N The number of nodes in the graph.
 * @param density The probability of an edge between two nodes.
 * @param w_min The minimum weight of an edge.
 * @param w_max The maximum weight of an edge.
 * @return A random graph with the specified properties.
 */
Graph generateRandomGraph(int N, double density, double w_min, double w_max)
{
    if (N < 0 || density < 0.0 || density > 1.0 || w_min > w_max)
    {
        throw invalid_argument("Parámetros inválidos para grafo aleatorio");
    }

    // Create an empty graph
    Graph g;

    // Add N nodes to the graph
    for (int i = 0; i < N; ++i)
    {
        g.addNode();
    }

    // Initialize random number generators
    GraphEngine rng(random_device{}()); // I add a secuence of random numbers from a seed based on the current time of the device
                                        // GraphEngine  rng(12345);  // semilla fija // for testing
    RealDist prob(0.0, 1.0);
    RealDist peso(w_min, w_max);

    // Add edges to the graph with probability density
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            if (prob(rng) < density) // Check if an edge should be added
            {
                // Check if the edge already exists
                if (g.hasEdge(i, j))
                {
                    continue; // Skip adding the edge if it already exists
                }

                // Add the edge with a random weight
                {
                    // Generate a random weight for the edge
                    double w = peso(rng);
                    g.addEdge(i, j, w);
                }
            }
        }
    }

    return g;
}
