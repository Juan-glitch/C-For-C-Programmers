#include "DijkstraAlgorithm.h"

using namespace std;

/**
 * @brief Default constructor.
 *
 * Creates a Point with a blank node (' ') and zero distance.
 */
Point::Point() = default;

/**
 * @brief Parameterized constructor.
 *
 * @param n The identifier of the node.
 * @param d The distance (cost) associated with this node.
 */
Point::Point(char n, float d) : node(n), distance(d) {}

/**
 * @brief Overloads the addition operator.
 *
 * Although not essential for Dijkstra, this operator lets you add the distances of two points.
 * @param other Another Point object.
 * @return A new Point with the same node and the sum of the distances.
 */
Point Point::operator+(const Point &other) const
{
    return Point(node, distance + other.distance);
}

/**
 * @brief Overloads the input stream operator.
 *
 * Reads a Point from an input stream.
 * @param is The input stream.
 * @param p  The Point to read into.
 * @return The input stream.
 */
std::istream &operator>>(std::istream &is, Point &p)
{
    return is >> p.node >> p.distance;
}

/**
 * @brief Overloads the output stream operator.
 *
 * Writes a Point to an output stream.
 * @param os The output stream.
 * @param p  The Point to write.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &os, const Point &p)
{
    return os << p.node << " " << p.distance;
}

/**
 * @brief Class implementing Dijkstra's algorithm for finding the shortest path.
 *
 * This class calculates the optimal path between a starting node and a destination node in a graph.
 * It uses a debug mode (controlled with a flag) to print detailed messages during each algorithm step.
 */
Dijkstra::Dijkstra(const Point &start,
                   const Point &end,
                   const std::map<char, std::vector<Point>> &graph,
                   bool debugMode)
    : startNode(start), endNode(end), graph(graph), debug(debugMode)
{
}

/**
 * @brief Prints the graph.
 *
 * Displays every node and its connections (like looking at a simple map of neighbors).
 */
void Dijkstra::printGraph() const
{
    for (const auto &node : graph)
    {
        cout << "Node: " << node.first << " Connections:" << endl;
        for (const auto &connection : node.second)
        {
            cout << "  [" << connection.node << ", " << connection.distance << "]" << endl;
        }
        cout << endl;
    }
}

/**
 * @brief Displays the nodes that have been visited.
 *
 * Shows which nodes have been finalized (visited) so far.
 */
void Dijkstra::displayVisited() const
{
    cout << "Visited nodes: ";
    for (const char &node : visited)
    {
        cout << node << " ";
    }
    cout << endl;
}

/**
 * @brief Initializes the distances for each node.
 *
 * Sets the starting node's distance to 0 and every other node's distance to infinity.
 * Think of this as knowing your home's distance (0) while all other locations are unknown (infinity).
 */
void Dijkstra::initializeDistances()
{
    for (const auto &node : graph)
    {
        char key = node.first;
        distances[key] = (key == startNode.node) ? Point(key, 0.0) : Point(key, INFINITY_VALUE);
    }
}

/**
 * @brief Displays the visited nodes.
 *
 * Prints all nodes that have already been processed.
 */
void Dijkstra::displayVisited() const
{
    cout << "Visited nodes: ";
    for (const char &node : visited)
    {
        cout << node << " ";
    }
    cout << endl;
}

/**
 * @brief Initializes the distances for each node.
 *
 * Sets the starting node's distance to 0 and every other node's distance to infinity.
 * Think of this as knowing your home's distance (0) while all other locations are unknown (infinity).
 */
void Dijkstra::initializeDistances()
{
    for (const auto &node : graph)
    {
        char key = node.first;
        distances[key] = (key == startNode.node) ? Point(key, 0.0) : Point(key, INFINITY_VALUE);
    }
}

/**
 * @brief Displays the current accumulated cost to each node.
 *
 * Shows the cost (distance) accumulated so far to reach every node.
 */
void Dijkstra::displayDistances() const
{
    for (const auto &pair : distances)
    {
        cout << "Node: " << pair.first << ", Distance: " << pair.second.distance << endl;
    }
}

/**
 * @brief Retrieves the unvisited node with the minimum provisional distance.
 *
 * Iterates over all nodes and selects the one that is unvisited and has the smallest known cost.
 * Think of it as finding the shortest unexplored road.
 *
 * @return The node identifier with the smallest accumulated cost, or ' ' if none is found.
 */
char Dijkstra::getMinimumNode() const
{
    float minValue = INFINITY_VALUE;
    char minNode = ' ';
    for (const auto &pair : distances)
    {
        if (visited.find(pair.first) == visited.end() && pair.second.distance < minValue)
        {
            minValue = pair.second.distance;
            minNode = pair.first;
        }
    }
    return minNode;
}

/**
 * @brief Updates the distances of the nodes adjacent to the current node.
 *
 * For each neighbor of the current node, if traveling through the current node offers a cheaper path,
 * update the neighbor's cost and mark the current node as its predecessor.
 *
 * @param currentNode The node from which to update neighboring nodes.
 */
void Dijkstra::updateDistances(char currentNode)
{
    // Loop through each connection (edge) from the current node.
    for (const auto &connection : graph[currentNode])
    {
        if (visited.find(connection.node) == visited.end())
        {
            // Calculate new distance: cost so far + cost from current to neighbor.
            float newDistance = distances[currentNode].distance + connection.distance;
            // If the new found path is shorter, update the cost for the neighbor.
            if (newDistance < distances[connection.node].distance)
            {
                distances[connection.node].distance = newDistance;
                predecessors[connection.node] = currentNode; // Record the predecessor.
            }
        }
    }
}

/**
 * @brief Reconstructs the shortest path from the destination back to the source.
 *
 * Walk backwards from the end node using the predecessor map until the start node is reached.
 *
 * @return A vector of node identifiers representing the shortest path.
 */
vector<char> Dijkstra::reconstructPath() const
{
    vector<char> path;
    char current = endNode.node;
    // Trace steps back until the starting node is reached.
    while (current != startNode.node)
    {
        path.push_back(current);
        // If a link is missing, then the path does not exist.
        if (predecessors.find(current) == predecessors.end())
        {
            return vector<char>(); // An empty vector indicates an error.
        }
        current = predecessors.at(current);
    }
    path.push_back(startNode.node);
    // Reverse the path to make it run from start to destination.
    reverse(path.begin(), path.end());
    return path;
}

/**
 * @brief Executes Dijkstra's algorithm.
 *
 * The algorithm performs the following steps:
 * 1. Find the unvisited node with the smallest distance.
 * 2. Mark that node as visited (it will not be checked again).
 * 3. Update (relax) the distances for each of its neighboring nodes.
 * 4. Repeat until all nodes are visited or the destination is reached.
 *
 * Debug mode outputs detailed information for every step executed.
 */
void Dijkstra::calculateDistances()
{
    int iteration = 0;
    while (visited.size() < distances.size())
    {
        // Step 1: Find the unvisited node with the smallest accumulated cost.
        char current = getMinimumNode();
        if (current == ' ')
            break; // No reachable unvisited node is found.

        // Mark the current node as visited.
        visited.insert(current);
        iteration++;
        if (debug)
        {
            cout << "Iteration " << iteration << ": Node " << current << " selected." << endl;
        }

        // Step 2: If the current node is the destination, then stop.
        if (current == endNode.node)
        {
            if (debug)
            {
                cout << "Destination node reached." << endl;
            }
            break;
        }

        // Step 3: Update the distances for each neighbor of the current node.
        updateDistances(current);
        if (debug)
        {
            cout << "Updated distances:" << endl;
            displayDistances();
        }
    }
    if (debug)
    {
        cout << "Total iterations: " << iteration << endl;
    }

    // Reconstruct and print the shortest path.
    vector<char> path = reconstructPath();
    if (!path.empty())
    {
        cout << "Shortest path:" << endl;
        for (char n : path)
        {
            cout << n << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found to the destination." << endl;
    }
}
