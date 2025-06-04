/*
 * ===========================================================================
 * Unidad 3: Introducción al concepto de Puntos y Constructores en C++
 * Curso: Programación Orientada a Objetos
 * Descripción:
 * Este script tiene como objetivo demostrar cómo se estructura y utiliza
 * una clase en C++ para modelar un punto en un plano cartesiano. Se explica
 * el uso de atributos privados, métodos públicos y constructores. Además,
 * se incluye una comparación conceptual con Python para resaltar cómo los
 * principios base son similares, aunque Python simplifica ciertos aspectos.
 * ===========================================================================
 */

#include <iostream>  /* Biblioteca estándar para manejo de entrada/salida */
using namespace std; /* Espacio de nombres estándar */

/* Definición de la clase Punto */
class Punto
{
 private:
  /* Atributos privados:
   * Representan las coordenadas del punto en un plano cartesiano.
   * Mantener estos atributos privados asegura que solo puedan ser accedidos
   * o modificados a través de métodos controlados. Esto promueve la encapsulación. */
  double x;
  double y;

 public:
  /* Constructor por defecto:
   * Este constructor inicializa el punto en el origen (0, 0).
   * En Python, esto se podría hacer simplemente definiendo __init__
   * con valores predeterminados para x e y. */
  Punto()
  {
    x = 0.0;
    y = 0.0;
    cout << "Constructor por defecto llamado. Punto en el origen (0, 0)." << endl;
  }

  /* Constructor con parámetros:
   * Permite inicializar el punto con valores específicos para las coordenadas.
   * En Python, esto también se realizaría en el método __init__, pasando
   * los valores directamente como argumentos. */
  Punto(double coordX, double coordY)
  {
    x = coordX;
    y = coordY;
    cout << "Constructor llamado. Punto en (" << x << ", " << y << ")." << endl;
  }

  /* Método público para mostrar las coordenadas del punto:
   * Este método es equivalente a definir una función en Python dentro de la clase.
   * En Python, se imprimiría directamente accediendo a los atributos del objeto. */
  void mostrarCoordenadas()
  {
    cout << "Las coordenadas del punto son (" << x << ", " << y << ")." << endl;
  }

  /* Método público para modificar las coordenadas del punto:
   * Permite actualizar las coordenadas de forma controlada.
   * En Python, sería posible modificar directamente los atributos si no fueran
   * "privados", pero es una buena práctica usar métodos específicos como este. */
  void establecerCoordenadas(double nuevaX, double nuevaY)
  {
    x = nuevaX;
    y = nuevaY;
    cout << "Nuevas coordenadas establecidas en (" << x << ", " << y << ")." << endl;
  }

  /* Destructor:
   * Se llama automáticamente cuando el objeto es destruido.
   * En Python, la recolección de basura elimina la necesidad de un destructor
   * explícito en la mayoría de los casos. Sin embargo, si se usa, se define
   * en el método especial __del__. */
  ~Punto()
  {
    cout << "Destructor llamado para el punto en (" << x << ", " << y << ")." << endl;
  }
};

int main()
{
  /* Creación de un objeto usando el constructor por defecto:
   * Esto inicializa el punto en el origen. En Python, sería tan simple como
   * crear una instancia sin pasar argumentos. */
  Punto punto1;

  /* Creación de un objeto usando el constructor con parámetros:
   * En Python, esto se haría pasando los valores directamente al método __init__. */
  Punto punto2(3.5, 7.8);

  /* Llamada a métodos públicos para interactuar con los atributos del objeto:
   * Estos métodos controlan el acceso a los atributos privados. En Python, podrías
   * hacer esto de manera similar usando métodos definidos dentro de la clase. */
  punto2.mostrarCoordenadas();
  punto2.establecerCoordenadas(10.0, 15.0);
  punto2.mostrarCoordenadas();

  return 0; /* Fin del programa principal */
}
