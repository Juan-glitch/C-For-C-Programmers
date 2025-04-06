#include <iostream>
#include <map>
#include <vector>
#include <limits> // Para usar valores máximos y minimos
#include <set>

using namespace std;
// Definir el infinito como una constante
const float INFINITO = numeric_limits<float>::max();
/* Definición de la clase Punto */
class punto
{
private:
    char nodo;
    float distancia;

public:
    // Constructor por defecto
    punto() : nodo(' '), distancia(0.0)
    {
        cout << "Constructor por defecto llamado. Punto inicializado." << endl;
    }

    // Constructor parametrizado
    punto(char n, float d) : nodo(n), distancia(d) {}

    // Sobrecarga del operador suma
    punto operator+(const punto &other) const
    {
        punto resultado;
        resultado.nodo = this->nodo;                             // Mantiene el nodo actual.
        resultado.distancia = this->distancia + other.distancia; // Suma las distancias.
        return resultado;
    }

    // Sobrecarga del operador istream (>>) para entrada formateada
    friend istream &operator>>(istream &is, punto &p)
    {
        cout << "Ingrese el nodo (carácter): ";
        is >> p.nodo;
        cout << "Ingrese la distancia (número flotante): ";
        is >> p.distancia;
        return is;
    }

    // Sobrecarga del operador ostream (<<) para salida formateada
    friend ostream &operator<<(ostream &os, const punto &p)
    {
        os << "Nodo: " << p.nodo << ", Distancia: " << p.distancia;
        return os;
    }
};

class Dijkstra
{
private:
    map<char, punto> distancias; // Guarda las distancias más cortas
    set<char> visitados;         // Conjunto de nodos ya visitados
public:
    punto nodo_inicial;
    punto nodo_final;
    // Constructor por defecto
    Dijkstra(const punto &inicial, const punto &final, const map<char, vector<punto>> &grafo)
        : nodo_inicial(inicial), nodo_final(final) {}

    void inicializar()
    {
        map<char, punto> distancias;
        for (const auto &nodo : grafo)
        {
            distancias[nodo.first] = punto(nodo.first, INFINITO); // Cada nodo comienza con distancia infinita.
        }
        distancias[nodo_inicial.nodo] = punto(nodo_inicial.nodo, 0.0); // El nodo inicial tiene distancia 0.
    }
    vector<punto> calcularDistancias(const map<char, vector<punto>> grafo)
    {
        float distancia = 0.0;
        for (auto &nodo : grafo)
        {
            // Inicializamos la distancia a infinito
            grafo[nodo_inicial.nodo].distancia = INFINITO;
        }
    }

}

main()
{
    // Definimos las conexiones entre nodos como constantes
    const map<char, vector<punto>> GRAFO = {
        {'A', {{'B', 5.0}, {'C', 2.0}}},             // Nodo A conectado a B y C
        {'B', {{'A', 5.0}, {'D', 3.0}, {'E', 7.0}}}, // Nodo B conectado a A, D y E
        {'C', {{'A', 2.0}, {'F', 4.0}}},             // Nodo C conectado a A y F
        {'D', {{'B', 3.0}, {'E', 1.0}}},             // Nodo D conectado a B y E
        {'E', {{'B', 7.0}, {'D', 1.0}, {'F', 6.0}}}, // Nodo E conectado a B, D y F
        {'F', {{'C', 4.0}, {'E', 6.0}}}              // Nodo F conectado a C y E
    };
    // Inicializamos variables
    uint8_t flag_end = 0;
    char nodo_inicial = 'A'; // Nodo inicial
    char nodo_final = 'F';   // Nodo final
    // Creamos un objeto de la clase Dijkstra
    Dijkstra dijkstra(punto(nodo_inicial, 0.0), punto(nodo_final, 0.0), GRAFO);

    while (flag_end == 0)
    {
    }

    return 0;
}
