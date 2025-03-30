# --------------------------------------------------------------------------------
# Usar Ubuntu 22.04 como imagen base, que trae versiones modernas de librerías y GLIBC.
# --------------------------------------------------------------------------------
FROM ubuntu:22.04

# --------------------------------------------------------------------------------
# Definir argumentos y etiquetas de metadatos.
# --------------------------------------------------------------------------------
ARG IMAGE_NAME="C/C++ Development Environment"
LABEL maintainer="JJ Arin <jjarin001@gmail.com>" \
    description="C/C++ Development Environment"

# --------------------------------------------------------------------------------
# Configurar el entorno para instalaciones no interactivas.
# --------------------------------------------------------------------------------
ENV DEBIAN_FRONTEND=noninteractive

# --------------------------------------------------------------------------------
# Actualizar el sistema e instalar las dependencias esenciales para desarrollo en C/C++.
#
# Se instalan:
#   - ccache: Para acelerar las compilaciones.
#   - clang, clang-format, clang-tidy: Compilador moderno y herramientas de formateo/análisis.
#   - cppcheck: Análisis estático de código.
#   - curl: Para transferencias de datos.
#   - doxygen: Generador de documentación.
#   - gcc: Compilador GNU.
#   - git: Sistema de control de versiones.
#   - graphviz: Para generación de gráficos.
#   - make y ninja-build: Herramientas de compilación.
#   - tar, unzip, vim, wget: Utilidades básicas.
#   - build-essential: Paquetes esenciales para compilar software.
#   - libssl-dev: Soporte para SSL.
# --------------------------------------------------------------------------------
RUN echo "Actualizando e instalando dependencias principales..." && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
    ccache \
    clang \
    clang-format \
    clang-tidy \
    cppcheck \
    curl \
    doxygen \
    gcc \
    git \
    graphviz \
    make \
    ninja-build \
    tar \
    unzip \
    vim \
    wget \
    build-essential \
    libssl-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# --------------------------------------------------------------------------------
# Instalar una versión actualizada de CMake (v3.26.3).
# Se remueve cualquier versión existente, se descarga el paquete,
# se extrae en /usr/local y se limpia la imagen.
# --------------------------------------------------------------------------------
RUN echo "Instalando una versión actualizada de CMake (v3.26.3)..." && \
    apt-get update && \
    apt-get install -y wget && \
    wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3-linux-x86_64.tar.gz && \
    tar -zxvf cmake-3.26.3-linux-x86_64.tar.gz --strip-components=1 -C /usr/local && \
    rm -f cmake-3.26.3-linux-x86_64.tar.gz && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# --------------------------------------------------------------------------------
# Instalar Conan, el gestor de paquetes para C/C++.
# Se instalan python3-setuptools y python3-pip, y luego Conan mediante pip3.
# --------------------------------------------------------------------------------
RUN echo "Instalando Conan package manager..." && \
    apt-get update && \
    apt-get install -y python3-setuptools python3-pip && \
    pip3 install --no-cache-dir conan && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# --------------------------------------------------------------------------------
# Instalar Catch2 (v3.3.2), el framework para pruebas unitarias en C/C++.
# Se clona el repositorio, se compila e instala, y finalmente se limpia.
# --------------------------------------------------------------------------------
RUN echo "Instalando Catch2 (v3.3.2)..." && \
    git clone --branch v3.3.2 --depth 1 https://github.com/catchorg/Catch2.git && \
    cd Catch2 && \
    cmake -Bbuild -S. -DBUILD_TESTING=OFF && \
    cmake --build build --target install && \
    cd .. && \
    rm -rf Catch2

# --------------------------------------------------------------------------------
# Instalar Google Test (GTest) (v1.13.0), otro framework de pruebas para C/C++.
# Se clona, se compila, se instala y se elimina el repositorio para ahorrar espacio.
# --------------------------------------------------------------------------------
RUN echo "Instalando Google Test (v1.13.0)..." && \
    git clone --branch v1.13.0 --depth 1 https://github.com/google/googletest.git && \
    cd googletest && \
    cmake -Bbuild -S. -Dgtest_disable_pthreads=1 && \
    cmake --build build --config Release && \
    cmake --build build --target install --config Release && \
    cd .. && \
    rm -rf googletest

# --------------------------------------------------------------------------------
# Instalar vcpkg, el gestor de paquetes de Microsoft para C/C++.
# Se clona el repositorio, se ejecuta el bootstrap y se elimina el directorio .git.
# --------------------------------------------------------------------------------
RUN echo "Instalando vcpkg..." && \
    git clone https://github.com/microsoft/vcpkg.git --depth 1 && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh -disableMetrics -useSystemBinaries && \
    cd .. && \
    rm -rf vcpkg/.git

# --------------------------------------------------------------------------------
# Establecer el directorio de trabajo para el código fuente.
# --------------------------------------------------------------------------------
WORKDIR /workspace

# --------------------------------------------------------------------------------
# Comando por defecto: mantiene el contenedor en ejecución.
# --------------------------------------------------------------------------------
CMD ["tail", "-f", "/dev/null"]
