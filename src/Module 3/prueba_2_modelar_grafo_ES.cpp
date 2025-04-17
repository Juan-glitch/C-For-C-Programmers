#include <vector>
#include <utility>   // para std::pair
#include <stdexcept> // para std::out_of_range
#include <iostream>

class Graph
{
public:
    // Constructor vacío: empezamos sin nodos
    Graph() = default;

    // "addNode()" añade un nuevo nodo al final
    // y devuelve su índice (0, 1, 2, …).
    int addNode()
    {
        adj.emplace_back();    // añade un vector vacío
        return adj.size() - 1; // índice del nodo creado
    }

    // "addEdge(u, v, w)" añade la arista (u→v) de peso w,
    // y si u o v no existían, lanza excepción.
    void addEdge(int u, int v, double w)
    {
        if (u < 0 || u >= (int)adj.size() ||
            v < 0 || v >= (int)adj.size())
        {
            throw std::out_of_range("Nodo inválido");
        }
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w); // como es no dirigido
    }

    // Devuelve referencia a la lista de vecinos de u
    const std::vector<std::pair<int, double>> &neighbors(int u) const
    {
        if (u < 0 || u >= (int)adj.size())
            throw std::out_of_range("Nodo inválido");
        return adj[u];
    }

    // Número de nodos actualmente en el grafo
    int size() const
    {
        return adj.size();
    }

private:
    // adj[i] = vector de pares (vecino, peso)
    std::vector<std::vector<std::pair<int, double>>> adj;
};

#include <map>

class LabeledGraph : public Graph
{
public:
    int addLabel(char label)
    {
        if (label2idx.count(label))
            return label2idx[label];
        int idx = addNode(); // del padre Graph
        label2idx[label] = idx;
        return idx;
    }

    void addEdge(char a, char b, double w)
    {
        int u = addLabel(a);
        int v = addLabel(b);
        Graph::addEdge(u, v, w);
    }

    // Devuelve el índice asociado a una etiqueta (lanza si no existe)
    int getIndex(char label) const
    {
        auto it = label2idx.find(label);
        if (it == label2idx.end())
            throw std::out_of_range("Etiqueta no existe");
        return it->second;
    }

private:
    std::map<char, int> label2idx;
};

int ejemplo_con_numeros()
{
    Graph g;

    // 1. Creamos, digamos, 3 nodos:
    int A = g.addNode(); // A == 0
    int B = g.addNode(); // B == 1
    int C = g.addNode(); // C == 2

    // 2. Ahora añadimos aristas con pesos:
    g.addEdge(A, B, 5.0); // entre 0 y 1 peso 5
    g.addEdge(B, C, 2.5); // entre 1 y 2 peso 2.5
    g.addEdge(A, C, 1.2); // entre 0 y 2 peso 1.2

    // 3. Consultamos los vecinos de B:
    for (auto [vecino, peso] : g.neighbors(B))
    {
        std::cout << "B -> " << vecino
                  << " con peso " << peso << "\n";
    }
    // Salida esperada:
    // B -> 0 con peso 5.0
    // B -> 2 con peso 2.5

    return 0;
}

int ejemplo_con_caracteres()
{
    LabeledGraph g;

    // Creamos explícitamente los tres nodos con sus etiquetas:
    g.addLabel('A');
    g.addLabel('B');
    g.addLabel('C');

    // Ahora addEdge ya no correrá addNode extra:
    g.addEdge('A', 'B', 5.0);
    g.addEdge('B', 'C', 2.5);
    g.addEdge('A', 'C', 1.2);

    // Consultamos vecinos de 'B':
    int idxB = g.getIndex('B');
    for (auto [vecino, peso] : g.neighbors(idxB))
    {
        std::cout << "B -> " << vecino
                  << " con peso " << peso << "\n";
    }

    return 0;
}
int main()
{
    ejemplo_con_numeros();
    ejemplo_con_caracteres();
    return 0;
}