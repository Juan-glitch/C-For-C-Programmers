#include <iostream>
#include <map>
#include <vector>
#include <limits> // Para usar valores máximos y mínimos
#include <set>
#include <algorithm> // Para reverse()

using namespace std;

// Definir el infinito como una constante
const float INFINITO = numeric_limits<float>::max();

// Definición de la clase Punto
class punto
{
public:
    char nodo;
    float distancia;

    // Constructor por defecto
    punto() : nodo(' '), distancia(0.0) {}

    // Constructor parametrizado
    punto(char n, float d) : nodo(n), distancia(d) {}

    // Sobrecarga del operador suma (no es esencial para Dijkstra)
    punto operator+(const punto &other) const
    {
        return punto(nodo, distancia + other.distancia);
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
    // Mapa de distancias más cortas a cada nodo
    map<char, punto> distancias;
    // Conjunto de nodos ya visitados
    set<char> visitados;
    // Mapa para guardar el nodo previo de cada nodo en la ruta óptima
    map<char, char> predecesores;

public:
    // Nodo inicial y final
    punto nodo_inicial;
    punto nodo_final;

    // Grafo representado como un mapa: cada clave es un nodo, y su valor es un vector de "punto"
    // que representa las conexiones: (nodo adyacente, costo)
    map<char, vector<punto>> grafo;

    // Constructor
    Dijkstra(const punto &inicial, const punto &final, const map<char, vector<punto>> &grafo)
        : nodo_inicial(inicial), nodo_final(final), grafo(grafo) {}

    // Función para imprimir el grafo
    void imprimirGrafo()
    {
        for (const auto &nodo : grafo)
        {
            cout << "Nodo: " << nodo.first << " Conexiones:" << endl;
            for (const auto &conexion : nodo.second)
            {
                cout << "  [" << conexion.nodo << ", " << conexion.distancia << "]" << endl;
            }
            cout << endl;
        }
    }

    // Muestra los nodos visitados
    void mostrarVisitados()
    {
        cout << "Nodos visitados: ";
        for (const char &nodo : visitados)
        {
            cout << nodo << " ";
        }
        cout << endl;
    }

    // Inicializa las distancias: 0 para el nodo inicial y ∞ para el resto
    void inicializarDistancias()
    {
        for (const auto &nodo : grafo)
        {
            char clave = nodo.first;
            distancias[clave] = (clave == nodo_inicial.nodo) ? punto(clave, 0.0) : punto(clave, INFINITO);
        }
    }

    // Muestra las distancias actuales a cada nodo
    void mostrarDistancias()
    {
        for (const auto &par : distancias)
        {
            cout << "Nodo: " << par.first << ", Distancia: " << par.second.distancia << endl;
        }
    }

    // Devuelve el nodo no visitado con la menor distancia provisional
    char obtenerNodoMinimo()
    {
        float minValor = INFINITO;
        char nodoMin = ' ';
        for (const auto &par : distancias)
        {
            if (visitados.find(par.first) == visitados.end() && par.second.distancia < minValor)
            {
                minValor = par.second.distancia;
                nodoMin = par.first;
            }
        }
        return nodoMin;
    }

    // Reconstruye el camino óptimo desde el nodo final al inicial usando los predecesores
    vector<char> reconstruirCamino()
    {
        vector<char> camino;
        char nodoActual = nodo_final.nodo;
        while (nodoActual != nodo_inicial.nodo)
        {
            camino.push_back(nodoActual);
            // Si no se encontró predecesor, significa que no existe camino
            if (predecesores.find(nodoActual) == predecesores.end())
            {
                return vector<char>(); // Camino vacío indica error
            }
            nodoActual = predecesores[nodoActual];
        }
        camino.push_back(nodo_inicial.nodo);
        reverse(camino.begin(), camino.end());
        return camino;
    }

    // Función que ejecuta el algoritmo Dijkstra, contando iteraciones y actualizando predecesores
    void calcularDistancias()
    {
        int iteracion = 0;
        while (visitados.size() < distancias.size())
        {
            // Seleccionamos el nodo con la mínima distancia entre los no visitados
            char actual = obtenerNodoMinimo();
            if (actual == ' ')
                break; // No quedan nodos alcanzables

            visitados.insert(actual);
            iteracion++;
            cout << "Iteración " << iteracion << ": Nodo " << actual << " seleccionado." << endl;

            // Si llegamos al nodo final, podemos detenernos
            if (actual == nodo_final.nodo)
            {
                cout << "Nodo final alcanzado." << endl;
                break;
            }

            // Analiza las aristas del nodo actual
            for (const auto &conexion : grafo[actual])
            {
                if (visitados.find(conexion.nodo) == visitados.end())
                {
                    float nuevaDistancia = distancias[actual].distancia + conexion.distancia;
                    if (nuevaDistancia < distancias[conexion.nodo].distancia)
                    {
                        distancias[conexion.nodo].distancia = nuevaDistancia;
                        predecesores[conexion.nodo] = actual; // Guardamos el camino
                    }
                }
            }
            // Para depurar, mostramos las distancias luego de cada iteración
            mostrarDistancias();
        }
        cout << "Número total de iteraciones: " << iteracion << endl;

        // Reconstruir y mostrar el camino óptimo si existe
        vector<char> camino = reconstruirCamino();
        if (!camino.empty())
        {
            cout << "Camino más corto: ";
            for (char n : camino)
            {
                cout << n << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "No se encontró un camino al destino." << endl;
        }
    }

    // Función principal para lanzar el algoritmo
    int main()
    {
        // Definición del grafo (ejemplo)
        const map<char, vector<punto>> GRAFO = {
            {'A', {{'B', 4.0}, {'C', 2.0}}},
            {'B', {{'A', 4.0}, {'C', 1.0}, {'D', 5.0}}},
            {'C', {{'A', 2.0}, {'B', 1.0}, {'D', 8.0}, {'E', 10.0}}},
            {'D', {{'B', 5.0}, {'C', 8.0}, {'E', 2.0}, {'F', 6.0}}},
            {'E', {{'C', 10.0}, {'D', 2.0}, {'F', 2.0}}},
            {'F', {{'D', 6.0}, {'E', 2.0}}}};

        // Declaramos nodo inicial y final
        char ini = 'A';
        char fin = 'F';

        // Creamos el objeto Dijkstra
        Dijkstra dijkstra(punto(ini, 0.0), punto(fin, 0.0), GRAFO);

        // Inicialización y ejecución
        dijkstra.inicializarDistancias();
        dijkstra.mostrarDistancias();
        dijkstra.imprimirGrafo();
        dijkstra.mostrarVisitados();
        dijkstra.calcularDistancias();

        return 0;
    }
};

int main()
{
    Dijkstra dijkstra(punto('A', 0.0), punto('F', 0.0), {{'A', {{'B', 5.0}, {'C', 2.0}}}, {'B', {{'A', 5.0}, {'D', 3.0}, {'E', 7.0}}}, {'C', {{'A', 2.0}, {'F', 4.0}}}, {'D', {{'B', 3.0}, {'E', 1.0}}}, {'E', {{'B', 7.0}, {'D', 1.0}, {'F', 6.0}}}, {'F', {{'C', 4.0}, {'E', 6.0}}}});
    dijkstra.inicializarDistancias();
    dijkstra.mostrarDistancias();
    dijkstra.imprimirGrafo();
    dijkstra.mostrarVisitados();
    dijkstra.calcularDistancias();
    return 0;
}
