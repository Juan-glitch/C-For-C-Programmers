#include "Graph.h"
using namespace std;

// Default constructor for the Graph class.
Graph::Graph() = default;

/**
 * @brief Adds a new node to the graph.
 *
 * This function appends an empty adjacency list for a new node
 * and returns the index of this newly added node.
 *
 * @return int The index of the newly added node.
 */
int Graph::addNode()
{
    // Add a new empty adjacency list for the new node.
    adj_.emplace_back();
    // Return the index of the newly added node.
    return static_cast<int>(adj_.size()) - 1;
}

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
void Graph::addEdge(int u, int v, double w)
{
    // Check if the node indices are within the valid range.
    if (u < 0 || u >= size() || v < 0 || v >= size())
    {
        // Throw an exception if the node indices are out of range.
        throw out_of_range("Invalid node index");
    }
    // Add an edge from node u to node v with weight w.
    adj_[u].emplace_back(v, w);
    // Add an edge from node v to node u with weight w.
    adj_[v].emplace_back(u, w);
}

/**
 * @brief Retrieves the neighbors of a node.
 *
 * This function returns a reference to the adjacency list of the node
 * at index u.
 *
 * @param u The index of the node.
 * @return const vector<pair<int, double>> & A reference to the adjacency list.
 */
const vector<pair<int, double>> &Graph::neighbors(int u) const
{
    // Check if the node index is within the valid range.
    if (u < 0 || u >= size())
    {
        // Throw an exception if the node index is out of range.
        throw out_of_range("Invalid node index");
    }
    // Return a reference to the adjacency list of the node.
    return adj_[u];
}

/**
 * @brief Retrieves the number of nodes in the graph.
 *
 * This function returns the size of the adjacency list.
 *
 * @return int The number of nodes in the graph.
 */
int Graph::size() const
{
    // Return the size of the adjacency list.
    return static_cast<int>(adj_.size());
}