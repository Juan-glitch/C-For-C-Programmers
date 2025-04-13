#include <iostream>
#include <map>
#include <vector>
#include <limits> // For using maximum/minimum values
#include <set>
#include <algorithm> // For reverse()

using namespace std;

/**
 * @brief Constant value representing infinity.
 */
const float INFINITY_VALUE = numeric_limits<float>::max();

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

    /**
     * @brief Default constructor.
     *
     * Creates a Point with a blank node (' ') and zero distance.
     */
    Point() : node(' '), distance(0.0) {}

    /**
     * @brief Parameterized constructor.
     *
     * @param n The identifier of the node.
     * @param d The distance (cost) associated with this node.
     */
    Point(char n, float d) : node(n), distance(d) {}

    /**
     * @brief Overloads the addition operator.
     *
     * Although not essential for Dijkstra, this operator lets you add the distances of two points.
     * @param other Another Point object.
     * @return A new Point with the same node and the sum of the distances.
     */
    Point operator+(const Point &other) const
    {
        return Point(node, distance + other.distance);
    }

    /**
     * @brief Overloaded input operator.
     *
     * Allows formatted input for a Point.
     * @param is Input stream.
     * @param p Point object to fill.
     * @return Reference to the input stream.
     */
    friend istream &operator>>(istream &is, Point &p)
    {
        cout << "Enter the node (character): ";
        is >> p.node;
        cout << "Enter the distance (floating point number): ";
        is >> p.distance;
        return is;
    }

    /**
     * @brief Overloaded output operator.
     *
     * Allows formatted output of a Point.
     * @param os Output stream.
     * @param p Point object to print.
     * @return Reference to the output stream.
     */
    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << "Node: " << p.node << ", Distance: " << p.distance;
        return os;
    }
};

/**
 * @brief Class implementing Dijkstra's algorithm for finding the shortest path.
 *
 * This class calculates the optimal path between a starting node and a destination node in a graph.
 * It uses a debug mode (controlled with a flag) to print detailed messages during each algorithm step.
 */
class Dijkstra
{
private:
    map<char, Point> distances;   ///< Map holding the accumulated cost for each node.
    set<char> visited;            ///< Set of nodes that have already been processed.
    map<char, char> predecessors; ///< Map to store the previous node for each node in the optimal path.
    bool debug;                   ///< Flag to indicate whether debug messages are printed.

public:
    Point startNode;                ///< The starting point.
    Point endNode;                  ///< The destination point.
    map<char, vector<Point>> graph; ///< Graph: each node maps to a vector of connections (neighbor and cost).

    /**
     * @brief Constructor for the Dijkstra algorithm class.
     *
     * Initializes the algorithm with the start node, destination node, the graph, and the debug flag.
     *
     * @param start The starting node.
     * @param end The destination node.
     * @param g The graph represented as a map.
     * @param debugMode Set to true to enable detailed debug messages.
     */
    Dijkstra(const Point &start, const Point &end, const map<char, vector<Point>> &g, bool debugMode = true)
        : startNode(start), endNode(end), graph(g), debug(debugMode) {}

    /**
     * @brief Prints the graph.
     *
     * Displays every node and its connections (like looking at a simple map of neighbors).
     */
    void printGraph() const
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
     * @brief Displays the visited nodes.
     *
     * Prints all nodes that have already been processed.
     */
    void displayVisited() const
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
    void initializeDistances()
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
    void displayDistances() const
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
    char getMinimumNode()
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
    void updateDistances(char currentNode)
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
    vector<char> reconstructPath() const
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
    void calculateDistances()
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
};

/**
 * @brief Main function.
 *
 * Defines an example graph, sets the start and destination nodes, and runs Dijkstra's algorithm
 * to determine the shortest path.
 *
 * @return int Exit status.
 */
int main()
{
    // Define an example graph: each node is associated with its connections and travel cost.
    const map<char, vector<Point>> GRAPH = {
        {'A', {{'B', 4.0}, {'C', 2.0}}},
        {'B', {{'A', 4.0}, {'C', 1.0}, {'D', 5.0}}},
        {'C', {{'A', 2.0}, {'B', 1.0}, {'D', 8.0}, {'E', 10.0}}},
        {'D', {{'B', 5.0}, {'C', 8.0}, {'E', 2.0}, {'F', 6.0}}},
        {'E', {{'C', 10.0}, {'D', 2.0}, {'F', 2.0}}},
        {'F', {{'D', 6.0}, {'E', 2.0}}}};

    // Set the starting and destination nodes.
    char start = 'A';
    char end = 'F';

    // Create a Dijkstra object with debug mode enabled.
    Dijkstra dijkstra(Point(start, 0.0), Point(end, 0.0), GRAPH, true);

    // Initialize known distances, display the graph, show visited nodes, and run the algorithm.
    dijkstra.initializeDistances();
    dijkstra.displayDistances();
    dijkstra.printGraph();
    dijkstra.displayVisited();
    dijkstra.calculateDistances();

    return 0;
}
