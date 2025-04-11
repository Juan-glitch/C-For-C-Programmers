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
public:
    char nodo;
    float distancia;
    // Constructor por defecto
    punto() : nodo(' '), distancia(0.0) {}

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
    map<char, vector<punto>> grafo; // Grafo representado como un mapa de nodos y sus conexiones
    // Constructor por defecto
    Dijkstra(const punto &inicial, const punto &final, const map<char, vector<punto>> &grafo)
    {
        this->nodo_inicial = inicial;
        this->nodo_final = final;
        this->grafo = grafo;
    }
    void imprimirGrafo()
    {
        for (const auto &nodo : grafo)
        {
            cout << "Nodo: " << nodo.first << " Conexiones: " << endl;
            for (const auto &conexion : nodo.second)
            {
                cout << "[" << conexion.nodo << ", " << conexion.distancia << "] " << endl;
            }
            cout << endl;
        }
    }
    void mostrarVisitados()
    {
        cout << "Nodos visitados: ";
        for (const char &nodo : visitados)
        {
            cout << nodo << " ";
        }
        cout << endl;
    }
    void inicializarDistancias()
    {
        for (const auto &nodo : grafo)
        {
            char clave = nodo.first;
            this->distancias[clave] = (clave == nodo_inicial.nodo) ? punto(clave, 0.0) : punto(clave, INFINITO);
        }
    }
    void mostrarDistancias()
    {
        for (const auto &par : distancias)
        {
            cout << "Clave: " << par.first << ", Distancia: " << par.second.distancia << endl;
        }
    }
    vector<punto> calcularDistancias()
    {
        visitados.insert(nodo_inicial.nodo);
        // Para cada nodo (clave) que aún no se ha visitado:
        for (const auto &clave : distancias)
        {
            cout << "Procesando clave: " << clave.first << endl;
            // Si ya está visitada la clave, la saltamos
            if (visitados.find(clave.first) != visitados.end())
                continue;

            bool conectado = false;       // Bandera que indica si el nodo tiene conexión con algún nodo visitado
            float mejorCamino = INFINITO; // Inicializamos con infinito para luego comparar los caminos

            // Recorremos todos los subnodos (conexiones) de la clave actual:
            for (const auto &subnodo : grafo[clave.first])
            {
                // Verificamos si podemos acceder a ese subnodo de algun nodo visitado
                if (visitados.find(subnodo.nodo) != visitados.end())
                {
                }
                // Verificamos si este subnodo (su identificador) se encuentra en el conjunto de visitados
                if (visitados.find(subnodo.nodo) != visitados.end())
                {
                    conectado = true;

                    // Calculamos el camino potencial: distancia hasta el subnodo + costo del enlace
                    float caminoPotencial = distancias[subnodo.nodo].distancia + subnodo.distancia;

                    // Actualizamos si encontramos un camino mejor:
                    if (caminoPotencial < mejorCamino)
                        mejorCamino = caminoPotencial;
                }
                // Si el subnodo no esta conectado pero enlaza
            }

            // Si el nodo está conectado a algún nodo visitado, actualizamos su distancia
            if (conectado && mejorCamino < clave.second.distancia)
            {
                // Aquí asignarías la nueva distancia al nodo actual
                // Por ejemplo:
                // distancias[clave.first].distancia = mejorCamino;
                // Además podrías, en este punto, marcar el nodo como visitado, si corresponde según la lógica de tu algoritmo.
            }
            // De lo contrario, si 'conectado' es false, significa que ningún subnodo de esta clave está conectado a los visitados,
            // por lo que no consideramos este nodo para actualización en esta iteración.
        }
        return vector<punto>();
    }
};
// Función principal

int main()
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

    dijkstra.inicializarDistancias();
    dijkstra.mostrarDistancias();
    dijkstra.imprimirGrafo();
    dijkstra.mostrarVisitados();
    dijkstra.calcularDistancias();

    return 0;
}
