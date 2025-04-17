// GraphGenerator.cpp
// ------------------
// Este script implementa un generador de grafos aleatorios parametrizable
// por número de nodos, densidad de aristas y rango de pesos.
// A continuación verás cada paso comentado para que puedas seguirlo e implementar por tu cuenta.

#include <vector>
#include <utility>
#include <random>
#include <iostream>

// ------------------------------------------------------------------------
// Paso 1: Define tu clase Graph (si no la tienes en un header separado).
// Aquí se copia la versión simplificada que vimos antes.

class Graph
{
public:
    Graph() = default;
    int addNode()
    {
        adj.emplace_back();
        return static_cast<int>(adj.size()) - 1;
    }
    void addEdge(int u, int v, double w)
    {
        if (u < 0 || u >= size() || v < 0 || v >= size())
            throw std::out_of_range("Nodo inválido");
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    const std::vector<std::pair<int, double>> &neighbors(int u) const
    {
        if (u < 0 || u >= size())
            throw std::out_of_range("Nodo inválido");
        return adj[u];
    }
    int size() const { return static_cast<int>(adj.size()); }

private:
    std::vector<std::vector<std::pair<int, double>>> adj;
};

// ------------------------------------------------------------------------
// Paso 2: Función de generación aleatoria.
// Parámetros:
//    - N: número de nodos
//    - density: probabilidad de existencia de cada arista (entre 0.0 y 1.0)
//    - w_min, w_max: rango de pesos continuo para cada arista

Graph generateRandomGraph(int N, double density, double w_min, double w_max)
{
    Graph g;
    // 2.1 Añade N nodos al grafo:
    for (int i = 0; i < N; ++i)
    {
        g.addNode();
    }

    // 2.2 Prepara el generador de números aleatorios:
    std::mt19937 rng(std::random_device{}());                  // motor
    std::uniform_real_distribution<double> prob(0.0, 1.0);     // para densidad
    std::uniform_real_distribution<double> peso(w_min, w_max); // para pesos

    // 2.3 Recorre cada posible par (i, j) con i < j:
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            if (prob(rng) < density)
            {
                double w = peso(rng);
                g.addEdge(i, j, w);
            }
        }
    }
    return g;
}

// ------------------------------------------------------------------------
// Paso 3: Función auxiliar para imprimir la lista de adyacencia:

void printGraph(const Graph &g)
{
    for (int u = 0; u < g.size(); ++u)
    {
        std::cout << u << ": ";
        for (auto &edge : g.neighbors(u))
        {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << '\n';
    }
}

// ------------------------------------------------------------------------
// Paso 4: Ejemplo de uso en main()

int main()
{
    int N = 50;
    double density = 0.2;
    double w_min = 1.0, w_max = 10.0;

    // Genera el grafo:
    Graph g = generateRandomGraph(N, density, w_min, w_max);

    // Muestra la representación (útil para depuración):
    printGraph(g);

    return 0;
}
