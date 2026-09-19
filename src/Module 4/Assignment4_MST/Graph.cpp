#include "Graph.h"
#include "utils/DisjointSet.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

Graph::Graph(int numberOfNodes)
    : nodeCount(numberOfNodes)
{
    if (nodeCount < 0)
    {
        throw std::invalid_argument("El numero de nodos no puede ser negativo");
    }
    adjacencyList.resize(static_cast<size_t>(nodeCount));
}

Graph::Graph(const std::string &filename)
    : nodeCount(0)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("No se pudo abrir el fichero: " + filename);
    }

    file >> nodeCount;
    if (file.fail() || nodeCount <= 0)
    {
        throw std::runtime_error("Formato invalido en el fichero: numero de nodos no valido");
    }

    adjacencyList.resize(static_cast<size_t>(nodeCount));

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
    if (weight < 0.0)
    {
        throw std::invalid_argument("El peso de la arista debe ser no negativo");
    }

    // Graph is undirected: insert edge in both directions
    adjacencyList[static_cast<size_t>(from)].push_back(std::make_pair(to, weight));
    adjacencyList[static_cast<size_t>(to)].push_back(std::make_pair(from, weight));
}

int Graph::getNodeCount() const
{
    return nodeCount;
}

int Graph::size() const
{
    return nodeCount;
}

bool Graph::hasEdge(int origin, int destiny) const
{
    if (origin < 0 || origin >= nodeCount || destiny < 0 || destiny >= nodeCount)
    {
        throw std::out_of_range("Indice de nodo fuera de rango");
    }

    const std::vector<std::pair<int, double>> &adj = adjacencyList[static_cast<size_t>(origin)];
    for (size_t i = 0; i < adj.size(); ++i)
    {
        if (adj[i].first == destiny)
        {
            return true;
        }
    }
    return false;
}

const std::vector<std::pair<int, double>> &Graph::neighbors(int u) const
{
    if (u < 0 || u >= nodeCount)
    {
        throw std::out_of_range("Indice de nodo fuera de rango");
    }
    return adjacencyList[static_cast<size_t>(u)];
}

std::vector<Edge> Graph::getEdges() const
{
    std::vector<Edge> edges;

    // Collect each undirected edge once (convention: from < to)
    for (int from = 0; from < nodeCount; ++from)
    {
        const std::vector<std::pair<int, double>> &adj = adjacencyList[static_cast<size_t>(from)];
        for (size_t i = 0; i < adj.size(); ++i)
        {
            int to = adj[i].first;
            double weight = adj[i].second;

            if (from < to)
            {
                Edge edge;
                edge.from = from;
                edge.to = to;
                edge.weight = weight;
                edges.push_back(edge);
            }
        }
    }

    return edges;
}

MSTResult Graph::minimumSpanningTree() const
{
    MSTResult result;
    result.totalCost = 0.0;

    if (nodeCount <= 1)
    {
        return result;
    }

    // 1. Retrieve and sort all edges by ascending weight (Kruskal's algorithm)
    std::vector<Edge> sortedEdges = getEdges();
    std::sort(sortedEdges.begin(), sortedEdges.end(),
              [](const Edge &a, const Edge &b)
              {
                  return a.weight < b.weight;
              });

    // 2. Greedily select edges using DisjointSet to detect and prevent cycles
    DisjointSet ds(nodeCount);

    for (size_t i = 0; i < sortedEdges.size(); ++i)
    {
        const Edge &edge = sortedEdges[i];
        if (ds.unite(edge.from, edge.to))
        {
            result.edges.push_back(edge);
            result.totalCost += edge.weight;

            // An MST on V vertices always contains exactly V - 1 edges
            if (static_cast<int>(result.edges.size()) == nodeCount - 1)
            {
                break;
            }
        }
    }

    // 3. Verify tree connectivity: an MST must connect all nodes (V - 1 edges)
    if (static_cast<int>(result.edges.size()) != nodeCount - 1)
    {
        throw std::runtime_error("El grafo no es conexo: no se pudo formar un arbol de expansion conexo");
    }

    return result;
}
