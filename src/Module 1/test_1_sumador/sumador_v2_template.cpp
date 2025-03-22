#include <iostream>  // Biblioteca para entrada y salida en C++.
#include <vector>    // Biblioteca para manejar vectores dinámicos en C++.

// Función que calcula la suma de los elementos de un vector.
// Parámetros:
// - const std::vector<int>& array: Usamos una referencia constante para evitar copias innecesarias y asegurar que el vector
// no se modifique. Retorno:
// - La suma de los elementos del vector como un entero.

// Declaración de la plantilla genérica
template<typename T>  // T es un parámetro genérico que representa cualquier tipo de dato.
T sumArray(const std::vector<T>& array)
{
  T sum = 0;  // Inicializamos la variable 'sum' en 0 para acumular la suma.

  // Usamos un bucle basado en rango (introducido en C++11) para recorrer el vector.
  // Ventaja: Es más legible y elimina la necesidad de manejar índices manualmente.
  for (T num : array)
  {
    sum += num;  // Añadimos cada elemento del vector a 'sum'.
  }
  return sum;  // Devolvemos el resultado final.
}

int main()
{
  // Usamos std::vector<int> para un ejemplo con enteros
  std::vector<int> intArray = { 10, 20, 30, 40, 50 };

  // Usamos std::vector<double> para un ejemplo con decimales
  std::vector<double> doubleArray = { 1.1, 2.2, 3.3, 4.4, 5.5 };

  // Llamamos a la función genérica para calcular la suma de ambos vectores
  int intSum = sumArray(intArray);           // Suma de enteros
  double doubleSum = sumArray(doubleArray);  // Suma de decimales

  // Mostramos los resultados
  std::cout << "Suma de enteros: " << intSum << std::endl;
  std::cout << "Suma de decimales: " << doubleSum << std::endl;
  std::cout << "Salida JJ" << std::endl;
  return 0;
}