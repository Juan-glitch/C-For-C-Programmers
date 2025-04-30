#include "Graph.h"
#include "LabeledGraph.h"
#include <cassert>
#include <iostream>

using namespace std;

/**
 * @brief Example of creating a graph with 3 nodes and 3 edges.
 *
 * We create 3 nodes and establish connections between them with weights.
 * Then we query the list of neighbors of one of the nodes and print them.
 *
 * @returns 0 if everything went well.
 */
int example_with_numbers()
{
    Graph g;

    // 1. We create, say, 3 nodes:
    int A = g.addNode(); // A == 0
    int B = g.addNode(); // B == 1
    int C = g.addNode(); // C == 2

    // 2. Now we add edges with weights:
    g.addEdge(A, B, 5.0); // between 0 and 1 weight 5
    g.addEdge(B, C, 2.5); // between 1 and 2 weight 2.5
    g.addEdge(A, C, 1.2); // between 0 and 2 weight 1.2

    // 3. We query the neighbors of B:
    for (auto [neighbor, weight] : g.neighbors(B))
    {
        cout << "B -> " << neighbor
             << " with weight " << weight << "\n";
    }
    // Expected output:
    // B -> 0 with weight 5.0
    // B -> 2 with weight 2.5

    return 0;
}

/**
 * @brief Example of creating a graph with 3 nodes and 3 edges, with labels.
 *
 * We create 3 nodes with labels and establish connections between them with weights.
 * Then we query the list of neighbors of one of the nodes and print them.
 *
 * @returns 0 if everything went well.
 */
int example_with_characters()
{
    LabeledGraph g;
    // 1. We explicitly create the three nodes with their labels:

    // We explicitly create the three nodes with their labels:
    g.addLabel('A');
    g.addLabel('B');
    g.addLabel('C');
    // 2. Now addEdge will not run addNode extra:
    g.addEdge('A', 'B', 5.0); // between A and B weight 5
    g.addEdge('B', 'C', 2.5); // between B and C weight 2.5
    g.addEdge('A', 'C', 1.2); // between A and C weight 1.2

    // Now addEdge will not run addNode extra:
    g.addEdge('A', 'B', 5.0);
    g.addEdge('B', 'C', 2.5);
    g.addEdge('A', 'C', 1.2);
    // 3. We query the neighbors of 'B':

    // We query the neighbors of 'B':
    int idxB = g.getIndex('B');
    for (auto [neighbor, weight] : g.neighbors(idxB))
    {
        cout << "B -> " << neighbor
             << " with weight " << weight << "\n";
        // Expected output:
        // B -> A with weight 5.0
        // B -> C with weight 2.5
    }

    return 0;
}

int main()
{
    example_with_numbers();
    example_with_characters();
    return 0;
}