#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100  // Tamaño máximo del array

// Función para convertir números separados por comas a un array
void parseNumbersToArray(const char *input, int array[], int *size)
{
  char *token;
  char *inputCopy = malloc(strlen(input) + 1);
  if (!inputCopy)
  {
    fprintf(stderr, "Error: no se pudo asignar memoria.\n");
    exit(EXIT_FAILURE);
  }
  strcpy(inputCopy, input);

  int index = 0;

  // Usamos strtok para dividir la cadena por comas
  token = strtok(inputCopy, ",");
  while (token != NULL && index < MAX_SIZE)
  {
    array[index++] = atoi(token);  // Convertimos cada número en entero
    token = strtok(NULL, ",");
  }

  *size = index;    // Almacenamos el tamaño del array
  free(inputCopy);  // Liberamos la memoria de la copia
}

// Función para sumar los valores de un array
int sumArray(int *array, int size)
{
  int sum = 0;
  // Sumamos los valores del array
  for (int i = 0; i < size; i++)
  {
    sum += array[i];
  }
  return sum;
}

int main()
{
  const char *input = "10,20,30,40,50";  // Ejemplo de entrada
  int array[MAX_SIZE];
  int size;
  int sum;

  // Llamamos a la función para llenar el array
  parseNumbersToArray(input, array, &size);

  // Calculamos la suma del array
  sum = sumArray(array, size);

  // Mostramos el resultado
  printf("Suma del Array resultante:\n");
  printf("%d\n", sum);

  return 0;
}
