#ifndef LABELEDGRAPH_H
#define LABELEDGRAPH_H

#include "Graph.h"
#include <map>
#include <string>
#include <stdexcept>

// Clase LabeledGraph: extiende Graph con etiquetas tipo char
class LabeledGraph : public Graph
{
public:
    int addLabel(char label);               // crea o recupera etiqueta
    void addEdge(char a, char b, double w); // versión etiquetada de addEdge
    int getIndex(char label) const;         // traduce etiqueta → índice

private:
    std::map<char, int> label2idx;
};

#endif // LABELEDGRAPH_H