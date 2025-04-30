#include "LabeledGraph.h"
using namespace std;

/**
 * @brief Adds a new label to the graph.
 *
 * This function checks if the label already exists, and if so, returns its index.
 * Otherwise, it adds a new node to the graph with the given label and returns its index.
 *
 * @param label The label to add.
 * @return int The index of the label.
 */
int LabeledGraph::addLabel(char label)
{
    // Check if the label already exists.
    auto it = label2idx.find(label);
    if (it != label2idx.end())
    {
        // Return the index of the existing label.
        return it->second;
    }
    // Add a new node to the graph with the given label.
    int idx = Graph::addNode();
    // Map the label to its index.
    label2idx[label] = idx;
    // Return the index of the new label.
    return idx;
}

/**
 * @brief Adds an undirected edge between two labeled nodes with a weight.
 *
 * This function adds an edge between the nodes with the given labels and weight.
 *
 * @param a The label of the first node.
 * @param b The label of the second node.
 * @param w The weight of the edge.
 */
void LabeledGraph::addEdge(char a, char b, double w)
{
    // Get the indices of the nodes with the given labels.
    int u = addLabel(a);
    int v = addLabel(b);
    // Add an edge between the nodes with the given weight.
    Graph::addEdge(u, v, w);
}

/**
 * @brief Retrieves the index of a label.
 *
 * This function throws an exception if the label does not exist.
 *
 * @param label The label to retrieve the index for.
 * @return int The index of the label.
 */
int LabeledGraph::getIndex(char label) const
{
    // Check if the label exists.
    auto it = label2idx.find(label);
    if (it == label2idx.end())
    {
        // Throw an exception if the label does not exist.
        throw out_of_range("Etiqueta no existe");
    }
    // Return the index of the label.
    return it->second;
}