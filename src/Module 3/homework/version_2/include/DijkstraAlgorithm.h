#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <map>
#include <vector>
#include <limits> // For std::numeric_limits
#include <set>
#include <algorithm> // For std::reverse

/**
 * @brief Constant value representing infinity.
 */
static constexpr float INFINITY_VALUE = std::numeric_limits<float>::max();

/**
 * @brief Class representing a point (node) in a graph.
 *
 * A Point holds a node identifier and the current accumulated distance (cost) to get there.
 */
class Point
{
public:
    char node;      ///< Identifier of the node.
    float distance; ///< Distance from the starting node.

    Point();
    Point(char n, float d);

    Point operator+(const Point &other) const;

    friend std::istream &operator>>(std::istream &is, Point &p);
    friend std::ostream &operator<<(std::ostream &os, const Point &p);
};

/**
 * @brief Class implementing Dijkstra's algorithm for finding the shortest path.
 *
 * This class calculates the optimal path between a starting node and a destination node in a graph.
 * It uses a debug mode (controlled with a flag) to print detailed messages during each algorithm step.
 */
class Dijkstra
{
public:
    /**
     * @brief Constructor.
     * @param start     The starting Point.
     * @param end       The destination Point.
     * @param graph     Adjacency list: for each node, a vector of (neighbor, cost).
     * @param debugMode If true, detailed debug output is printed.
     */
    Dijkstra(const Point &start,
             const Point &end,
             const std::map<char, std::vector<Point>> &graph,
             bool debugMode = true);

    /// Print the entire graph (nodes and their connections).
    void printGraph() const;

    /// Display which nodes have been visited so far.
    void displayVisited() const;

    /// Display the current known distances to all nodes.
    void displayDistances() const;

    /// Initialize distances: 0 for start node, infinity for all others.
    void initializeDistances();

    /// Run Dijkstra's algorithm and (optionally) print debug info.
    void calculateDistances();

    /// Reconstruct and return the shortest path from start to destination.
    std::vector<char> reconstructPath() const;

private:
    std::map<char, Point> distances;   ///< Current best-known distance for each node.
    std::set<char> visited;            ///< Set of nodes already finalized.
    std::map<char, char> predecessors; ///< For each node, the previous node on the shortest path.
    bool debug;                        ///< Whether to print debug output.

    Point startNode;                          ///< The start Point.
    Point endNode;                            ///< The end Point.
    std::map<char, std::vector<Point>> graph; ///< Adjacency list representation.

    /// Find the unvisited node with the smallest tentative distance.
    char getMinimumNode() const;

    /// Relax edges outgoing from the given node.
    void updateDistances(char currentNode);
};

#endif // DIJKSTRA_H
