# --------------------------------------------------------------------------------
# Usar una imagen base actualizada.
# Ubuntu 22.04 trae versiones modernas del sistema y librerías (p.ej., GLIBC)
# que soportan herramientas de desarrollo recientes.
# --------------------------------------------------------------------------------
    FROM ubuntu:22.04

    # Define un argumento para el nombre del entorno.
    ARG IMAGE_NAME="C/C++ Development Environment"
    
    # Etiquetas de metadatos con información del mantenedor y la descripción.
    LABEL maintainer="JJ Arin <jjarin001@gmail.com>" \
          description="C/C++ Development Environment"
    
    # Configuración para evitar ventanas interactivas durante la instalación.
    ENV DEBIAN_FRONTEND=noninteractive
    
    # --------------------------------------------------------------------------------
    # Actualiza el sistema e instala dependencias esenciales para el desarrollo en C/C++.
    #
    # Se instalan:
    #   - ccache: para acelerar las compilaciones.
    #   - clang, clang-format, clang-tidy: compilador moderno y herramientas de formateo/análisis.
    #   - cppcheck: análisis estático de código.
    #   - curl: para transferencias de datos.
    #   - doxygen: para generar documentación.
    #   - gcc: compilador GNU.
    #   - git: sistema de control de versiones.
    #   - graphviz: para generación de gráficos.
    #   - make y ninja-build: herramientas de compilación.
    #   - tar, unzip, vim, wget: utilidades básicas.
    #   - build-essential y libssl-dev: paquetes esenciales para compilar software y soporte SSL.
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
    # Instalar una versión actualizada de CMake.
    # Elimina cualquier versión instalada, descarga CMake v3.26.3 y la extrae en /usr/local.
    # Se usa --no-check-certificate en wget para evitar problemas con la verificación del certificado.
    # --------------------------------------------------------------------------------
    RUN echo "Instalando una versión actualizada de CMake (v3.26.3)..." && \
        apt-get remove -y cmake || true && \
        apt-get update && \
        apt-get install -y wget && \
        wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3-linux-x86_64.tar.gz && \
        tar -zxvf cmake-3.26.3-linux-x86_64.tar.gz --strip-components=1 -C /usr/local && \
        rm -f cmake-3.26.3-linux-x86_64.tar.gz && \
        apt-get clean && \
        rm -rf /var/lib/apt/lists/*
    
    # --------------------------------------------------------------------------------
    # Instalar Conan, el gestor de paquetes para C/C++.
    # Se instala python3-setuptools y python3-pip (necesarios para ejecutar pip3)
    # y se instala Conan mediante pip3.
    # --------------------------------------------------------------------------------
    RUN echo "Instalando Conan package manager..." && \
        apt-get update && \
        apt-get install -y python3-setuptools python3-pip && \
        pip3 install --no-cache-dir conan && \
        apt-get clean && \
        rm -rf /var/lib/apt/lists/*
    
    # --------------------------------------------------------------------------------
    # Instalar Catch2, el framework para pruebas unitarias en C/C++.
    # Se clona el repositorio de Catch2 (v3.3.2), se compila e instala,
    # y se elimina el código fuente para reducir el tamaño de la imagen.
    # --------------------------------------------------------------------------------
    RUN echo "Instalando Catch2 (v3.3.2)..." && \
        git clone --branch v3.3.2 --depth 1 https://github.com/catchorg/Catch2.git && \
        cd Catch2 && \
        cmake -Bbuild -S. -DBUILD_TESTING=OFF && \
        cmake --build build --target install && \
        cd .. && \
        rm -rf Catch2
    
    # --------------------------------------------------------------------------------
    # Instalar Google Test (GTest), otro framework de pruebas para C/C++.
    # Se clona el repositorio de Google Test (v1.13.0), se compila, se instala,
    # y se limpia el repositorio.
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
    # Se clona la rama principal del repositorio, se compila y se elimina el directorio .git.
    # --------------------------------------------------------------------------------
    RUN echo "Instalando vcpkg..." && \
        git clone https://github.com/microsoft/vcpkg.git --depth 1 && \
        cd vcpkg && \
        ./bootstrap-vcpkg.sh -disableMetrics -useSystemBinaries && \
        cd .. && \
        rm -rf vcpkg/.git
    
    # --------------------------------------------------------------------------------
    # Establece el directorio de trabajo donde se ubicará el código fuente.
    # --------------------------------------------------------------------------------
    WORKDIR /workspace
    
    # --------------------------------------------------------------------------------
    # Comando por defecto
    # --------------------------------------------------------------------------------
    CMD ["tail", "-f", "/dev/null"]
    