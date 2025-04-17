#include <iostream>
#include <map>
#include <vector>
#include <limits> // Para usar valores máximos y mínimos
#include <set>
#include <algorithm> // Para reverse()

using namespace std;

/**
 * @brief Valor constante para representar la distancia infinita.
 */
const float INFINITO = numeric_limits<float>::max();

/**
 * @brief Clase que representa un punto o nodo en un grafo.
 *
 * Contiene un identificador (nodo) y la distancia actual (coste acumulado para llegar a él).
 */
class punto
{
public:
    char nodo;       ///< Identificador del nodo.
    float distancia; ///< Distancia al nodo desde el origen.

    /**
     * @brief Constructor por defecto.
     */
    punto() : nodo(' '), distancia(0.0) {}

    /**
     * @brief Constructor parametrizado.
     * @param n Identificador del nodo.
     * @param d Distancia asociada al nodo.
     */
    punto(char n, float d) : nodo(n), distancia(d) {}

    /**
     * @brief Sobrecarga del operador suma.
     *
     * Permite sumar la distancia de dos puntos. (No es esencial para Dijkstra)
     * @param other Otro objeto punto.
     * @return Un nuevo objeto punto con la suma de las distancias.
     */
    punto operator+(const punto &other) const
    {
        return punto(nodo, distancia + other.distancia);
    }

    /**
     * @brief Sobrecarga del operador de entrada.
     *
     * Permite formatear la entrada de un punto.
     * @param is Flujo de entrada.
     * @param p Objeto punto a llenar.
     * @return Referencia al flujo de entrada.
     */
    friend istream &operator>>(istream &is, punto &p)
    {
        cout << "Ingrese el nodo (carácter): ";
        is >> p.nodo;
        cout << "Ingrese la distancia (número flotante): ";
        is >> p.distancia;
        return is;
    }

    /**
     * @brief Sobrecarga del operador de salida.
     *
     * Permite imprimir de forma formateada un punto.
     * @param os Flujo de salida.
     * @param p Objeto punto a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend ostream &operator<<(ostream &os, const punto &p)
    {
        os << "Nodo: " << p.nodo << ", Distancia: " << p.distancia;
        return os;
    }
};

/**
 * @brief Clase que implementa el algoritmo de Dijkstra para encontrar el camino más corto.
 *
 * Esta clase calcula el camino óptimo entre un nodo inicial y uno final en un grafo.
 * Además, al activar el modo debug, se imprimen los pasos y cambios realizados en cada iteración.
 */
class Dijkstra
{
private:
    map<char, punto> distancias;  ///< Mapa con las distancias (coste acumulado) para cada nodo.
    set<char> visitados;          ///< Conjunto de nodos que ya fueron procesados.
    map<char, char> predecesores; ///< Mapa para almacenar el "nodo anterior" en el camino óptimo.
    bool debug;                   ///< Indica si se muestran mensajes de depuración.

public:
    punto nodo_inicial;             ///< Nodo de partida.
    punto nodo_final;               ///< Nodo destino.
    map<char, vector<punto>> grafo; ///< Grafo: cada nodo tiene un vector de conexiones (nodo y coste).

    /**
     * @brief Constructor de la clase Dijkstra.
     *
     * Inicializa el algoritmo con el nodo inicial, final, el grafo y el flag de debug.
     * @param inicial Nodo de inicio.
     * @param final Nodo destino.
     * @param grafo Grafo representado como un mapa.
     * @param debugMode Si es true se activan los mensajes de depuración.
     */
    Dijkstra(const punto &inicial, const punto &final, const map<char, vector<punto>> &grafo, bool debugMode = true)
        : nodo_inicial(inicial), nodo_final(final), grafo(grafo), debug(debugMode) {}

    /**
     * @brief Imprime el grafo.
     *
     * Muestra cada nodo y sus conexiones (como si fueras un mapa simple para entender vecindarios).
     */
    void imprimirGrafo() const
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

    /**
     * @brief Muestra los nodos ya visitados.
     */
    void mostrarVisitados() const
    {
        cout << "Nodos visitados: ";
        for (const char &nodo : visitados)
        {
            cout << nodo << " ";
        }
        cout << endl;
    }

    /**
     * @brief Inicializa las distancias de cada nodo.
     *
     * Asigna 0 al nodo inicial y ∞ (infinito) para el resto, es decir,
     * imagina que solo conoces la distancia cero de tu casa y el resto aún son desconocidas (infinito).
     */
    void inicializarDistancias()
    {
        for (const auto &nodo : grafo)
        {
            char clave = nodo.first;
            distancias[clave] = (clave == nodo_inicial.nodo) ? punto(clave, 0.0) : punto(clave, INFINITO);
        }
    }

    /**
     * @brief Muestra las distancias actuales de cada nodo.
     *
     * Imprime el coste acumulado para llegar a cada nodo hasta el momento.
     */
    void mostrarDistancias() const
    {
        for (const auto &par : distancias)
        {
            cout << "Nodo: " << par.first << ", Distancia: " << par.second.distancia << endl;
        }
    }

    /**
     * @brief Obtiene el nodo no visitado con la menor distancia provisional.
     *
     * Recorre todos los nodos y elige el que aún no has "visitado" y que tiene el coste más bajo.
     * Piensa en ello como buscar la calle más corta que aún no hayas explorado.
     *
     * @return El identificador del nodo con el menor camino acumulado o ' ' si ninguno está disponible.
     */
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

    /**
     * @brief Actualiza las distancias de los nodos adyacentes.
     *
     * Para cada conexión de tu nodo actual, si ir a ese vecino desde dónde estás resulta más barato,
     * actualiza su distancia y marca tu nodo como su "anterior" (esto ayudará a formar el camino óptimo).
     *
     * @param nodoActual El nodo desde el que se actualizan los caminos.
     */
    void actualizarDistancias(char nodoActual)
    {
        // Recorre todas las conexiones del nodo actual
        for (const auto &conexion : grafo[nodoActual])
        {
            if (visitados.find(conexion.nodo) == visitados.end())
            {
                // Calcula la nueva distancia: lo que has recorrido + el coste para ir al vecino.
                float nuevaDistancia = distancias[nodoActual].distancia + conexion.distancia;
                // Si esta nueva ruta es mejor (más corta) que la que tenías, la actualizas.
                if (nuevaDistancia < distancias[conexion.nodo].distancia)
                {
                    distancias[conexion.nodo].distancia = nuevaDistancia;
                    predecesores[conexion.nodo] = nodoActual; // Guarda el paso anterior.
                }
            }
        }
    }

    /**
     * @brief Reconstruye el camino óptimo de regreso del destino al origen.
     *
     * Retrocede desde el nodo destino hasta el nodo de inicio usando los predecesores
     * que se establecieron durante la actualización de distancias.
     *
     * @return Un vector de nodos que representa el camino más corto.
     */
    vector<char> reconstruirCamino() const
    {
        vector<char> camino;
        char nodoActual = nodo_final.nodo;
        // Mientras no lleguemos a la casa (nodo inicial), vamos agregando cada nodo.
        while (nodoActual != nodo_inicial.nodo)
        {
            camino.push_back(nodoActual);
            if (predecesores.find(nodoActual) == predecesores.end())
            {
                return vector<char>(); // Si falta un eslabón, se considera error (camino vacío).
            }
            nodoActual = predecesores.at(nodoActual);
        }
        camino.push_back(nodo_inicial.nodo);
        // Invertimos para que el camino vaya desde el inicio hasta el destino.
        reverse(camino.begin(), camino.end());
        return camino;
    }

    /**
     * @brief Ejecuta el algoritmo de Dijkstra.
     *
     * Realiza los siguientes pasos:
     * 1. Busca el nodo sin visitar con la menor distancia (¡elige el camino más corto conocido!).
     * 2. Lo marca como visitado (ya no se vuelve a consultar).
     * 3. Actualiza las distancias de sus nodos vecinos (si encuentra un camino más barato, lo usa).
     * 4. Repite hasta haber visitado todos los nodos o haber llegado al destino.
     *
     * Si el modo debug está activado, imprime mensajes que te muestran cada paso del algoritmo.
     */
    void calcularDistancias()
    {
        int iteracion = 0;
        while (visitados.size() < distancias.size())
        {
            // Paso 1: Encuentra el nodo con la menor distancia que aún no se ha visitado.
            char actual = obtenerNodoMinimo();
            if (actual == ' ')
                break; // Si no se encuentra ningún nodo, termina el algoritmo.

            // Marca el nodo como visitado para no volver a evaluarlo.
            visitados.insert(actual);
            iteracion++;
            if (debug)
            {
                cout << "Iteración " << iteracion << ": Nodo " << actual << " seleccionado." << endl;
            }

            // Paso 2: Si el nodo actual es el destino final, sal del ciclo.
            if (actual == nodo_final.nodo)
            {
                if (debug)
                {
                    cout << "Nodo final alcanzado." << endl;
                }
                break;
            }

            // Paso 3: Actualiza las distancias de cada vecino del nodo actual.
            actualizarDistancias(actual);
            if (debug)
            {
                cout << "Actualización de distancias:" << endl;
                mostrarDistancias();
            }
        }
        if (debug)
        {
            cout << "Número total de iteraciones: " << iteracion << endl;
        }

        // Reconstrucción del camino óptimo recorrido.
        vector<char> camino = reconstruirCamino();
        if (!camino.empty())
        {
            cout << "Camino más corto: " << endl;
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
};

/**
 * @brief Función principal.
 *
 * En esta función se define un grafo de ejemplo, se establecen el nodo de inicio y destino,
 * y se ejecuta el algoritmo de Dijkstra para encontrar el camino más corto.
 *
 * @return int Código de salida del programa.
 */
int main()
{
    // Definición del grafo de ejemplo: cada nodo tiene sus conexiones y el coste para ir a cada uno.
    const map<char, vector<punto>> GRAFO = {
        {'A', {{'B', 4.0}, {'C', 2.0}}},
        {'B', {{'A', 4.0}, {'C', 1.0}, {'D', 5.0}}},
        {'C', {{'A', 2.0}, {'B', 1.0}, {'D', 8.0}, {'E', 10.0}}},
        {'D', {{'B', 5.0}, {'C', 8.0}, {'E', 2.0}, {'F', 6.0}}},
        {'E', {{'C', 10.0}, {'D', 2.0}, {'F', 2.0}}},
        {'F', {{'D', 6.0}, {'E', 2.0}}}};

    // Declaramos el nodo inicial y final.
    char ini = 'A';
    char fin = 'F';

    // Creamos un objeto Dijkstra:
    // Se activa el modo debug (true) para que se muestren los pasos detallados.
    Dijkstra dijkstra(punto(ini, 0.0), punto(fin, 0.0), GRAFO, true);

    // Inicializa las distancias conocidas, imprime información del grafo, muestra nodos visitados y ejecuta el algoritmo.
    dijkstra.inicializarDistancias();
    dijkstra.mostrarDistancias();
    dijkstra.imprimirGrafo();
    dijkstra.mostrarVisitados();
    dijkstra.calcularDistancias();

    return 0;
}

// Generador de grafos aleatorio
// Nuestra funcion tendra que efectuar la gestion de memoria de manera inteligente.

bool **graph;
srand(time(0)); // seed rand()
graph = new bool *[size];
for (int i = 0; i < size; ++i)
    graph[i] = new bool[size];
// heap created 2 D array of Bool