#include "GraphGenerator.h"
#include <random>
#include <iostream>
#include <stdexcept>
#include "Graph.h"

using namespace std;

using GraphEngine = std::mt19937;
using RealDist = std::uniform_real_distribution<double>;

/**
 * Ensure that no node in the graph is isolated, i.e. that the graph is connected.
 * This is done by adding a random edge between each isolated node and any other
 * node in the graph.
 *
 * @param g The graph to modify.
 * @param N The number of nodes in the graph.
 * @param rng A random number generator.
 * @param weightDist A distribution to generate random weights for the edges.
 */
static void ensureAllConnected(Graph &g, int N, GraphEngine &rng, RealDist &weightDist)
{
    // Step: Ensure no node is isolated
    for (int i = 0; i < N; ++i)
    {
        // if node i tiene grado 0
        if (g.neighbors(i).empty())
        {
            // elige un nodo j distinto de i al azar
            int j;
            do
            {
                j = rng() % N; // rng es tu mt19937
            } while (j == i);
            // genera un peso aleatorio
            double w = weightDist(rng);
            // añade la arista i–j
            g.addEdge(i, j, w);
        }
    }
}

/**
 * Generates a random graph with N nodes, edge density, and weight range.
 *
 * @param N The number of nodes in the graph.
 * @param density The probability of an edge between two nodes.
 * @param w_min The minimum weight of an edge.
 * @param w_max The maximum weight of an edge.
 * @return A random graph with the specified properties.
 */
Graph generateRandomGraph(int N, double density, double w_min, double w_max, bool ensureConnected = false)
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

    // Iterate over every possible undirected edge exactly once:
    // - Skip self-loops (i == j)
    // - Avoid duplicate edges (i,j) and (j,i)
    for (int i = 0; i < N; ++i)
    {
        // Start j at i+1 so we only consider pairs (i,j) with j > i
        for (int j = i + 1; j < N; ++j)
        {
            // With probability `density`, add the edge
            if (prob(rng) < density)
            {
                // If our Graph class already guards against duplicates,
                // this check is optional—but shows intent clearly:
                if (g.hasEdge(i, j))
                {
                    continue; // Edge already exists; skip
                }

                // Generate a random weight in [w_min, w_max)
                double w = peso(rng);
                g.addEdge(i, j, w);
            }
        }
    }

    // Ensure no isolated nodes if requested
    if (ensureConnected)
    {
        ensureAllConnected(g, N, rng, peso);
    }

    return g;
}
