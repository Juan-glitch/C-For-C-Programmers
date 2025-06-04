#include <iostream>
#include <vector>  // Para usar std::vector
using namespace std;

// Función plantilla para calcular la suma de un array
template<typename T>
T sum(const std::vector<T>& array)
{
  if (array.empty())
    return T();  // Devuelve 0 si el vector está vacío.
  T total = 0;   // Inicializa la suma.
  for (T num : array)
  {
    total += num;  // Acumula la suma.
  }
  return total;  // Devuelve el resultado.
}

// Función plantilla para calcular la resta de un array
template<typename T>
T resta(const std::vector<T>& array)
{
  if (array.empty())
    return T();         // Devuelve 0 si el vector está vacío.
  T result = array[0];  // Inicializa con el primer elemento.
  for (size_t i = 1; i < array.size(); ++i)
  {                      // Comienza en el segundo elemento.
    result -= array[i];  // Resta cada elemento restante.
  }
  return result;  // Devuelve el resultado final.
}

// Función plantilla para imprimir los elementos de un array
template<typename T>
void printArray(const std::vector<T>& array)
{
  for (const T& elem : array)
  {
    cout << elem << " ";  // Imprime cada elemento separado por un espacio.
  }
  cout << endl;  // Nueva línea al final.
}

int main()
{
  cout << "Demonstrate templates" << endl;

  // Usamos std::vector en lugar de arrays estáticos
  std::vector<int> a = { 1, 2, 3 };
  std::vector<double> b = { 2.1, 2.2, 2.3 };

  // Suma
  cout << "Suma del array a: " << sum(a) << endl;
  cout << "Suma del array b: " << sum(b) << endl;

  // Resta
  cout << "Resta del array a: " << resta(a) << endl;
  cout << "Resta del array b: " << resta(b) << endl;

  // Imprimir los arrays
  cout << "Elementos del array a: ";
  printArray(a);
  cout << "Elementos del array b: ";
  printArray(b);

  return 0;
}
