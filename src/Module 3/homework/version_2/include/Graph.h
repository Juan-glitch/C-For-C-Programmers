
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <stdexcept>

// Clase Graph: representación mediante lista de adyacencia
class Graph
{
public:
    Graph();                                                           // constructor
    int addNode();                                                     // añade un nodo y devuelve su índice
    void addEdge(int u, int v, double w);                              // añade arista no dirigida
    const std::vector<std::pair<int, double>> &neighbors(int u) const; // vecinos de un nodo
    int size() const;                                                  // número de nodos

private:
    std::vector<std::vector<std::pair<int, double>>> adj_; // lista de adyacencia
};

#endif // GRAPH_H