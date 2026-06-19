#include "Graph.h"
#include "utils/DisjointSet.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

Graph::Graph(int numberOfNodes)
    : nodeCount(numberOfNodes)
{
    adjacencyList.resize(nodeCount);
}

Graph::Graph(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("No se pudo abrir el fichero: " + filename);
    }

    file >> nodeCount;
    if (file.fail() || nodeCount <= 0)
    {
        throw std::runtime_error("Formato invalido en el fichero: numero de nodos no valido");
    }

    adjacencyList.resize(nodeCount);

    int from = 0;
    int to = 0;
    double weight = 0.0;
    while (file >> from >> to >> weight)
    {
        addEdge(from, to, weight);
    }
}

void Graph::addEdge(int from, int to, double weight)
{
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount)
    {
        throw std::out_of_range("Indice de nodo fuera de rango");
    }

    adjacencyList[from].emplace_back(to, weight);
    adjacencyList[to].emplace_back(from, weight);
}

int Graph::getNodeCount() const
{
    return nodeCount;
}

std::vector<Edge> Graph::getEdges() const
{
    std::vector<Edge> edges;

    for (int from = 0; from < nodeCount; ++from)
    {
        for (const auto &[to, weight] : adjacencyList[from])
        {
            if (from < to)
            {
                edges.push_back({from, to, weight});
            }
        }
    }

    return edges;
}

MSTResult Graph::minimumSpanningTree() const
{
    std::vector<Edge> sortedEdges = getEdges();

    std::sort(sortedEdges.begin(), sortedEdges.end(),
              [](const Edge &a, const Edge &b)
              {
                  return a.weight < b.weight;
              });

    DisjointSet ds(nodeCount);
    MSTResult result{0.0, {}};

    for (const auto &edge : sortedEdges)
    {
        if (ds.unite(edge.from, edge.to))
        {
            result.edges.push_back(edge);
            result.totalCost += edge.weight;
        }
    }

    return result;
}
