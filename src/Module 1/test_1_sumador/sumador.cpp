#include <iostream>  // Biblioteca para entrada y salida en C++.
#include <vector>    // Biblioteca para manejar vectores dinámicos en C++.

// Función que calcula la suma de los elementos de un vector.
// Parámetros:
// - const std::vector<int>& array: Usamos una referencia constante para evitar copias innecesarias y asegurar que el vector
// no se modifique. Retorno:
// - La suma de los elementos del vector como un entero.
int sumArray(const std::vector<int>& array)
{
  int sum = 0;  // Inicializamos la variable 'sum' en 0 para acumular la suma.

  // Usamos un bucle basado en rango (introducido en C++11) para recorrer el vector.
  // Ventaja: Es más legible y elimina la necesidad de manejar índices manualmente.
  for (int num : array)
  {
    sum += num;  // Añadimos cada elemento del vector a 'sum'.
  }
  return sum;  // Devolvemos el resultado final.
}

int main()
{
  // Ejemplo de vector inicializado con valores.
  // Ventaja de std::vector: Manejo dinámico del tamaño. No necesitamos especificar el tamaño máximo como en C.
  std::vector<int> array = { 10, 20, 30, 40, 50 };

  // Llamamos a la función sumArray para calcular la suma de los elementos del vector.
  // Paso por referencia en lugar de copia para mejorar el rendimiento.
  int sum = sumArray(array);

  // Mostramos el resultado de la suma en la consola usando std::cout.
  // Ventaja: Mejor integración con otros elementos del lenguaje y soporte para múltiples tipos de datos.
  std::cout << "Suma del Array resultante: " << sum << std::endl;

  // Nota: 'std::endl' añade un salto de línea al final del mensaje y asegura que el flujo se vacíe correctamente.
  return 0;  // Indicamos que el programa finalizó correctamente.
}
