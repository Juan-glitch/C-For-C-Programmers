#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept>
#include <vector>
#include <utility>

/**
 * @brief The Graph class represents an undirected graph using an adjacency list.
 */
class Graph
{
public:
    /**
     * @brief Default constructor for the Graph class.
     */
    Graph();

    /**
     * @brief Retrieves the number of nodes in the graph.
     *
     * This function returns the size of the adjacency list.
     *
     * @return int The number of nodes in the graph.
     */
    int size() const;

    /**
     * @brief Adds a new node to the graph.
     *
     * This function appends an empty adjacency list for a new node
     * and returns the index of this newly added node.
     *
     * @return int The index of the newly added node.
     */
    int addNode();

    /**
     * @brief Adds an undirected edge between two nodes with a weight.
     *
     * This function adds an edge from node u to node v with weight w,
     * and also adds an edge from node v to node u with weight w,
     * since the graph is undirected.
     *
     * @param u The index of the first node.
     * @param v The index of the second node.
     * @param w The weight of the edge.
     */
    void addEdge(int u, int v, double w);

    /**
     * @brief Checks if an edge exists between two nodes.
     *
     * This function checks if there is an edge from node u to node v.
     *
     * @param origin The index of the first node.
     * @param destiny The index of the second node.
     * @return bool True if the edge exists, false otherwise.
     */
    bool hasEdge(int origin, int destiny) const;

    /**
     * @brief Retrieves the neighbors of a node.
     *
     * This function returns a reference to the adjacency list of the node
     * at index u.
     *
     * @param u The index of the node.
     * @return const std::vector<std::pair<int, double>>& A reference to the adjacency list.
     */
    const std::vector<std::pair<int, double>> &neighbors(int u) const;

private:
    std::vector<std::vector<std::pair<int, double>>> adj_; ///< Adjacency list representation of the graph.
};

#endif // GRAPH_H
