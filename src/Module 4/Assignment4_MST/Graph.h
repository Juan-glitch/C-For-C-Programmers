#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <utility>
#include "model/Edge.h"
#include "model/MSTResult.h"

/**
 * @brief Represents an undirected, weighted graph with non-negative edge costs.
 *
 * Supports graph construction directly by node count or by loading edge lists
 * from a text file. Provides methods to compute the Minimum Spanning Tree (MST)
 * using Kruskal's algorithm with DisjointSet (Union-Find).
 */
class Graph {
public:
    /**
     * @brief Constructs an empty graph with a fixed number of nodes.
     * @param numberOfNodes Total number of vertices (must be non-negative).
     */
    Graph(int numberOfNodes);

    /**
     * @brief Constructs a graph by reading nodes and edges from a formatted file.
     *
     * File format:
     *   <number_of_nodes>
     *   <from> <to> <weight>
     *   ...
     *
     * @param filename Path to the input file.
     * @throws std::runtime_error If the file cannot be opened or has an invalid format.
     */
    Graph(const std::string &filename);

    /**
     * @brief Adds an undirected weighted edge between two vertices.
     *
     * Since the graph is undirected, the edge is recorded in both directions.
     *
     * @param from Origin vertex index (0-based).
     * @param to Destination vertex index (0-based).
     * @param weight Non-negative edge weight.
     * @throws std::out_of_range If vertex indices are out of valid bounds [0, nodeCount).
     */
    void addEdge(int from, int to, double weight);

    /**
     * @brief Returns the total number of nodes in the graph.
     * @return Number of nodes.
     */
    int getNodeCount() const;

    /**
     * @brief Retrieves the number of nodes in the graph.
     * @return Number of nodes.
     */
    int size() const;

    /**
     * @brief Checks if an undirected edge exists between two nodes.
     * @param origin First vertex index.
     * @param destiny Second vertex index.
     * @return true if an edge connects origin and destiny, false otherwise.
     */
    bool hasEdge(int origin, int destiny) const;

    /**
     * @brief Retrieves the adjacent neighbors and edge weights of a node.
     * @param u Vertex index.
     * @return Reference to vector of (neighbor, weight) pairs.
     */
    const std::vector<std::pair<int, double>> &neighbors(int u) const;

    /**
     * @brief Retrieves all unique undirected edges in the graph.
     *
     * Each undirected edge is listed once with from < to.
     *
     * @return Vector of Edge structs.
     */
    std::vector<Edge> getEdges() const;

    /**
     * @brief Computes the Minimum Spanning Tree (MST) using Kruskal's algorithm.
     *
     * Sorts edges by weight in ascending order and iteratively unites components
     * using DisjointSet, ensuring no cycles are created.
     *
     * @return MSTResult containing the total cost and the V - 1 spanning edges.
     * @throws std::runtime_error If the graph is disconnected (fewer than V - 1 edges formed).
     */
    MSTResult minimumSpanningTree() const;

private:
    int nodeCount;
    std::vector<std::vector<std::pair<int, double>>> adjacencyList;
};

#endif // GRAPH_H
