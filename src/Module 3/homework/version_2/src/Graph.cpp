#include "Graph.h"
#include <stdexcept>
#include <vector>
#include <utility>
using namespace std;

// Default constructor for the Graph class.
Graph::Graph() = default;

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
 * @brief Checks if an edge exists between two nodes.
 *
 * This function checks if there is an edge from node u to node v.
 *
 * @param origin The index of the first node.
 * @param destiny The index of the second node.
 * @return bool True if the edge exists, false otherwise.
 */
bool Graph::hasEdge(int origin, int destiny) const
{
    // Check if the node indices are within the valid range.
    if (origin < 0 || origin >= size() || destiny < 0 || destiny >= size())
    {
        // Throw an exception if the node indices are out of range.
        throw out_of_range("Invalid node index");
    }
    // Iterate through the adjacency list of node u to check for an edge to v.
    for (const auto &[neighbor, weight] : adj_[origin])
    {
        if (neighbor == destiny)
        {
            return true; // Edge exists
        }
    }
    return false; // Edge does not exist
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
