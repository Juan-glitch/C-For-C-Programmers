/**
 * Curso: C++ For C Programmers
 * Homework 3: Minimum Spanning Tree (MST) usando el algoritmo de Kruskal.
 *
 * Programa autocontenido en un solo archivo:
 * - Lee un grafo conexo ponderado no dirigido desde fichero.
 * - Formato de entrada: <num_nodos> seguido de triples <i> <j> <coste>.
 * - Calcula el MST utilizando Kruskal con Disjoint-Set (Union-Find).
 * - Imprime las aristas del árbol y el coste total acumulado.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <string>

// Estructura para representar una arista ponderada no dirigida
struct Edge {
    int from;
    int to;
    double weight;

    // Operador para ordenar aristas por peso de menor a mayor
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Estructura Disjoint-Set (Union-Find) con compresión de caminos y unión por rango
struct DisjointSet {
    std::vector<int> parent;
    std::vector<int> rank;

    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Cada nodo empieza siendo su propio representante
        }
    }

    // Encuentra la raíz del conjunto con compresión de caminos
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    // Une dos subconjuntos; devuelve false si ya estaban conectados (detecta ciclo)
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) {
            return false; // Forman ciclo
        }

        // Unión por rango
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

// Clase Graph para gestionar vértices, aristas y el cálculo del MST
class Graph {
private:
    int nodeCount;
    std::vector<Edge> edges;

public:
    Graph(int n = 0) : nodeCount(n) {}

    // Constructor que carga el grafo desde fichero
    Graph(const std::string& filename) : nodeCount(0) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("No se pudo abrir el fichero: " + filename);
        }

        file >> nodeCount;
        if (file.fail() || nodeCount <= 0) {
            throw std::runtime_error("Formato de fichero invalido: numero de nodos incorrecto");
        }

        int u = 0, v = 0;
        double w = 0.0;
        while (file >> u >> v >> w) {
            addEdge(u, v, w);
        }
    }

    void addEdge(int u, int v, double w) {
        edges.push_back({u, v, w});
    }

    int getNodeCount() const {
        return nodeCount;
    }

    int size() const {
        return nodeCount;
    }

    // Algoritmo de Kruskal: devuelve el coste total y rellena mstEdges
    double kruskalMST(std::vector<Edge>& mstEdges) const {
        mstEdges.clear();
        double totalCost = 0.0;

        // 1. Ordenar aristas en orden ascendente de peso
        std::vector<Edge> sortedEdges = edges;
        std::sort(sortedEdges.begin(), sortedEdges.end());

        // 2. Seleccionar aristas codiciosamente evitando ciclos
        DisjointSet ds(nodeCount);
        for (const auto& e : sortedEdges) {
            if (ds.unite(e.from, e.to)) {
                mstEdges.push_back(e);
                totalCost += e.weight;

                // Un árbol de expansión siempre tiene exactamente V - 1 aristas
                if (static_cast<int>(mstEdges.size()) == nodeCount - 1) {
                    break;
                }
            }
        }

        // 3. Validar conectividad
        if (nodeCount > 1 && static_cast<int>(mstEdges.size()) != nodeCount - 1) {
            throw std::runtime_error("El grafo no es conexo: no se pudo formar un MST completo");
        }

        return totalCost;
    }
};

int main(int argc, char* argv[]) {
    // Si no se especifica archivo, usa uno por defecto o solicita argumento
    if (argc < 2) {
        std::cout << "Uso: " << argv[0] << " <archivo_de_grafo>" << std::endl;
        std::cout << "Ejemplo: " << argv[0] << " mst_data.txt" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    try {
        Graph g(filename);
        std::vector<Edge> mstEdges;
        double totalCost = g.kruskalMST(mstEdges);

        std::cout << "Minimum Spanning Tree" << std::endl << std::endl;
        for (const auto& e : mstEdges) {
            std::cout << e.from << " - " << e.to << " : " << e.weight << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Total cost: " << totalCost << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
