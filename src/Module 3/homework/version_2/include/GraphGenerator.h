#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "Graph.h"

/**
 * @brief Generates a random graph with N nodes, edge density, and weight range.
 *
 * @param N The number of nodes in the graph.
 * @param density The probability of an edge between two nodes.
 * @param w_min The minimum weight of an edge.
 * @param w_max The maximum weight of an edge.
 * @param ensureConnected If true, the resulting graph is ensured to be connected.
 * @return A random graph with the specified properties.
 */
Graph generateRandomGraph(int N, double density, double w_min, double w_max, bool ensureConnected);

#endif // GRAPH_GENERATOR_H