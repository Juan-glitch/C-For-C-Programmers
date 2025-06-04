# **C++ For C Programmers, Part A** (los 5 módulos que la componen):



# Apuntes y Ejercicios – Curso de C++ en Coursera

Este repositorio ha sido creado para acompañar el proceso de aprendizaje en el curso de C++ que estoy realizando en Coursera, en particular la especialización **C++ For C Programmers, Part A**. Aquí se recopilan apuntes, ejemplos y ejercicios conforme se avanza en cada módulo del curso. Actualmente, el directorio se organiza en función de los módulos vistos y en preparación para los contenidos de la especialización.

## Estructura del Proyecto

```
app
├── .devcontainer
├── .env
├── .github
│   ├── ISSUE_TEMPLATE
│   └── workflows
├── .vscode
├── cmake
├── resources
├── src
│   ├── Module 1
│   │   └── test_1_sumador
│   │       ├── sumador.c
│   │       ├── sumador.cpp
│   │       └── sumador_v2_template.cpp
│   ├── Module 2
│   │   ├── comprension_structura.cpp
│   │   └── uso_template.cpp
│   ├── common
│   └── tmp.cpp
└── test
    └── src
        └── tmp_test.cpp
```

### Descripción de Directorios

- **app**: Contiene la configuración del entorno (Docker, VSCode, GitHub Actions, etc.).
- **src**: Código fuente organizado en módulos:
  - **Module 1**: Ejercicios iniciales (ej. implementación de un sumador en C y C++).  
    - `sumador.c`: Versión en C.  
    - `sumador.cpp` y `sumador_v2_template.cpp`: Versiones en C++ con ejemplos de templates.
  - **Module 2**: Ejercicios del módulo actual:
    - `comprension_structura.cpp`: Ejemplo enfocado en la comprensión y manipulación de estructuras.
    - `uso_template.cpp`: Ejemplo práctico del uso de templates en C++.
  - **common**: Funciones y código reutilizable entre módulos.
  - `tmp.cpp`: Archivo para pruebas y experimentación.
- **test**: Pruebas unitarias y ejemplos de testing (por ejemplo, `tmp_test.cpp`).

## Contenido del Curso: C++ For C Programmers, Part A

Esta especialización (ofrecida por la Universidad de California, Santa Cruz) está compuesta por 5 módulos. A continuación, se detalla brevemente el contenido que se aborda en cada uno:

### Módulo 1: Conversión de Programas en C a C++

- **Objetivo:** Aprender a convertir programas escritos en C a C++.
- **Contenido:**
  - Introducción y organización del curso.
  - Cómo convertir un programa en C a C++.
  - Uso de la entrada/salida con seguridad en C++.
  - Ventajas y mejoras de C++ frente a C.
  - Ejercicios prácticos de conversión y adaptación del código.  

### Módulo 2: Funciones, Templates y Estructuras de Datos

- **Objetivo:** Introducir conceptos de funciones genéricas (templates) y estructuras de datos.
- **Contenido:**
  - Revisión del algoritmo de Dijkstra y su aplicación a estructuras de datos.
  - Definición y uso de funciones en C++.
  - Introducción a templates (funciones y clases genéricas).
  - Ejemplos prácticos usando estructuras como "Point" para modelar datos.  

### Módulo 3: Programación Orientada a Objetos y Gestión de Memoria

- **Objetivo:** Consolidar la programación orientada a objetos y el manejo adecuado de la memoria.
- **Contenido:**
  - Introducción a clases y objetos en C++.
  - Uso de constructores, constructores de copia y destructores.
  - Diferencias entre copia superficial y copia profunda (shallow vs. deep copy).
  - Gestión de listas y asignación dinámica de memoria.
  - Prácticas sobre inicialización de objetos y manejo de recursos.

### Módulo 4: Algoritmos Avanzados y Uso de la STL

- **Objetivo:** Profundizar en algoritmos avanzados y familiarizarse con la Standard Template Library (STL).
- **Contenido:**
  - Implementación de algoritmos de Prim y Kruskal para árboles generadores mínimos.
  - Uso de contenedores básicos de la STL (vectores, listas, etc.).
  - Introducción a iteradores y a las funcionalidades de la STL.
  - Empleo de características de C++11 (auto, for-each, etc.) para escribir código más conciso.
  - Ejercicios prácticos para afianzar estos conceptos.

### Módulo 5: Evaluación Final y Práctica

- **Objetivo:** Evaluar y consolidar todo lo aprendido en la especialización.
- **Contenido:**
  - Examen final y práctica integral de todos los conceptos vistos.
  - Ejercicios y proyectos finales.
  - Retroalimentación y peer review para mejorar y validar los conocimientos adquiridos.

Puedes revisar el contenido oficial del Módulo 2 de la especialización en el siguiente enlace:  
[Module 2 – Curso de C++ en Coursera](https://www.coursera.org/learn/c-plus-plus-a/home/module/2) 

## Cómo Navegar y Usar Este Repositorio

- **Navegación por Módulos:**
  - **Module 1 (src/Module 1):** Contiene ejercicios y ejemplos del primer módulo, enfocados en la conversión de programas en C a C++.
  - **Module 2 (src/Module 2):** Contiene ejemplos actuales relacionados con la comprensión de estructuras y el uso de templates, reflejando los temas del Módulo 2 del curso.
- **Pruebas y Experimentación:**
  - Utiliza `tmp.cpp` para realizar pruebas o desarrollar nuevas ideas.
  - El directorio `test` incluye ejemplos de pruebas unitarias para validar tu código.

## Consideraciones Adicionales

- **Entorno Docker:** El proyecto está configurado para ejecutarse dentro de un contenedor Docker, lo que garantiza que el entorno de desarrollo se mantenga consistente en diferentes máquinas.
- **Actualización Continua:** A medida que avances en el curso, se recomienda actualizar este documento o crear nuevas secciones para reflejar los nuevos aprendizajes y prácticas.
- **Referencia al Curso:** Siempre es útil contrastar tus apuntes con el contenido oficial del curso en Coursera para profundizar en conceptos y resolver dudas.

## Conclusión

Este repositorio es una herramienta viva para organizar mis apuntes y ejercicios del curso. Con una estructura clara y documentada, permite retomar el estudio en cualquier momento y sirve de guía tanto para mí como para cualquier persona que desee aprender C++ siguiendo esta metodología.

---

¡Espero que este README te sea de gran ayuda para seguir tu progreso en el curso y para que, en futuras consultas, puedas retomar el estudio y la práctica de cada módulo de manera ordenada y clara!