# Usar una imagen base estable
FROM ubuntu:18.04

ARG IMAGE_NAME=C/C++ Development Environment
LABEL maintainer="JJ Arin  <jjarin001@gmail.com>"
LABEL description="C/C++ Development Environment"

# Configuración inicial
ENV DEBIAN_FRONTEND=noninteractive

# Actualizar e instalar dependencias principales
RUN echo "Updating and installing system dependencies..." && \
    apt-get update && apt-get upgrade -y && \
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
        python3 \
        python3-pip \
        tar \
        unzip \
        vim \
        wget \
        build-essential \
        libssl-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Instalar CMake desde fuente
RUN echo "Installing CMake from source..." && \
    wget https://github.com/Kitware/CMake/releases/download/v3.15.0/cmake-3.15.0.tar.gz && \
    tar -zxvf cmake-3.15.0.tar.gz && \
    cd cmake-3.15.0 && \
    ./bootstrap && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf cmake-3.15.0*

# Instalar Conan (gestor de paquetes para C++)
RUN echo "Installing Conan package manager..." && \
    pip3 install --no-cache-dir conan

# Instalar Catch2
RUN echo "Installing Catch2 testing framework..." && \
    git clone https://github.com/catchorg/Catch2.git && \
    cd Catch2 && \
    cmake -Bbuild -H. -DBUILD_TESTING=OFF && \
    cmake --build build/ --target install && \
    cd .. && \
    rm -rf Catch2

# Instalar Google Test (GTest)
RUN echo "Installing Google Test framework..." && \
    git clone https://github.com/google/googletest.git --branch release-1.10.0 && \
    cd googletest && \
    cmake -Bbuild -Dgtest_disable_pthreads=1 && \
    cmake --build build --config Release && \
    cmake --build build --target install --config Release && \
    cd .. && \
    rm -rf googletest

# Instalar Vcpkg
RUN echo "Installing vcpkg package manager..." && \
    git clone https://github.com/microsoft/vcpkg -b 2020.06 && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh -disableMetrics -useSystemBinaries && \
    cd .. && \
    rm -rf vcpkg/.git

# Directorio de trabajo
WORKDIR /workspace

# Comando por defecto
CMD ["/bin/bash"]
