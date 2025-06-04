// Ira Pohl
// Copyright 2016
// Ejemplo suplementario sobre sobrecarga de operadores

#include <cstdint>
#include <iostream>

/*
    Esto simplifica el uso de funciones y tipos de la biblioteca estándar
    al evitar que tengas que escribir `std::` antes de cada uno.
    Es como dejar de poner el prefijo internacional antes de marcar un número de teléfono.
*/
using namespace std;

/*
    Aquí definimos un tipo enumerado `days` que representa los días de la semana.
    Se utiliza `enum class` en lugar de `enum` para garantizar **seguridad de tipo**,
    lo que evita conversiones accidentales entre este tipo y números enteros.

    Además, especificamos que el tipo subyacente será un entero de 8 bits (`std::int8_t`),
    lo cual es como usar una caja del tamaño perfecto para guardar nuestros valores.
*/
enum class days : std::int8_t
{
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
};

/*
    Sobrecargamos el operador de inserción (`<<`) para poder imprimir un valor de `days`.
    Sin esta sobrecarga, `std::cout` no sabría interpretar un valor de `days` directamente.
    Lo convertimos a entero con `static_cast<int>(d)` para representarlo.

    Metáfora: Es como enseñarle un idioma nuevo a alguien. Antes de esto, `std::cout`
    no entiende cómo mostrar `days`, pero le enseñamos cómo traducirlo.
*/
ostream& operator<<(ostream& out, const days& d)
{
  out << static_cast<int>(d);  // Convertimos el valor de `days` a su representación numérica.
  return out;                  // Devolvemos el flujo de salida actualizado.
}

/*
    Sobrecargamos el operador prefijo (`++x`) para incrementar el valor de un día.
    Usamos `static_cast` para convertir el valor actual a entero, sumarle 1 y asegurarnos
    de que, después de `SATURDAY`, vuelva a `SUNDAY` gracias al operador `% 7`.

    Metáfora: Es como un calendario infinito; los días de la semana se reinician cíclicamente.
*/
days operator++(days& d)
{
  d = static_cast<days>((static_cast<int>(d) + 1) % 7);  // Incremento cíclico.
  return d;                                              // Devolvemos el nuevo valor.
}

/*
    Sobrecargamos el operador postfijo (`x++`), que funciona de manera similar,
    pero devuelve el valor original **antes** de incrementar.

    Diferencia clave: Se guarda una copia temporal (`temp`) del día antes de actualizarlo,
    lo cual es útil si necesitas el valor anterior.
*/
days operator++(days& d, int)
{
  days temp = d;                                         // Guardamos el valor actual.
  d = static_cast<days>((static_cast<int>(d) + 1) % 7);  // Incremento cíclico.
  return temp;                                           // Devolvemos el valor original.
}

/*
    Función principal:
    En esta función demostramos cómo funcionan las enumeraciones de clase (`enum class`)
    y los operadores sobrecargados (`<<` y `++`).
*/
int main()
{
  days today{ days::MONDAY };  // Inicializamos el día como lunes.
  std::cout << "Demonstrate class enum" << std::endl;

  // Imprimimos el valor actual del día (convertido a entero por el operador `<<`).
  std::cout << "MONDAY VALUE IS " << today << std::endl;

  // Usamos el operador prefijo `++` para incrementar el día y mostrar el nuevo valor.
  std::cout << "INCREMENT VALUE IS " << ++today << std::endl;

  // Usamos el operador postfijo `++` para incrementar el día, pero mostramos el valor antiguo.
  std::cout << "INCREMENT VALUE IS " << today++ << std::endl;

  // Comprobamos que el valor del día se haya actualizado correctamente.
  std::cout << "INCREMENT VALUE IS " << today << std::endl;

  return 0;  // Finalizamos el programa.
}
