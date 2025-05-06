#include "Graph.h"
#include "DijkstraAlgorithm.h"
#include "GraphUtils.h"

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
    const Graph GRAPH = {
        {'A', {{'B', 4.0}, {'C', 2.0}}},
        {'B', {{'A', 4.0}, {'C', 1.0}, {'D', 5.0}}},
        {'C', {{'A', 2.0}, {'B', 1.0}, {'D', 8.0}, {'E', 10.0}}},
        {'D', {{'B', 5.0}, {'C', 8.0}, {'E', 2.0}, {'F', 6.0}}},
        {'E', {{'C', 10.0}, {'D', 2.0}, {'F', 2.0}}},
        {'F', {{'D', 6.0}, {'E', 2.0}}}};

    /**
     *      A
     *     / \
     *   4/   \2
     *   /     \
     *  B-------C
     *  | \1   /|\
     *  |  \  / | \
     * 5|   D  8| 10
     *  |  / \  | /
     *  | /6  \ |/2
     *  F-------E
     *      2
     */

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
