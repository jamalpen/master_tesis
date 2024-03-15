# Usaré una imagen base de ubuntu
FROM ubuntu:20.04

# Evitar preguntas de frontend durante la instalación de paquetes
ARG DEBIAN_FRONTEND=noninteractive

# Instalar dependencias necesarias
RUN apt-get update && apt-get install -y \
    cmake \
    cmake-curses-gui \
    gcc \
    g++ \
    libexpat1-dev \
    qt5-default \
    qtbase5-dev \
    libxmu-dev \
    libmotif-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*
    
# Descargar e instalar Xerces-C (ajusta según la versión necesaria)
RUN wget https://archive.apache.org/dist/xerces/c/3/sources/xerces-c-3.2.3.tar.gz \
    && tar -zxf xerces-c-3.2.3.tar.gz \
    && cd xerces-c-3.2.3 \
    && ./configure \
    && make -j$(nproc) \
    && make install \
    && cd .. \
    && rm -rf xerces-c-3.2.3 \
    && rm xerces-c-3.2.3.tar.gz
    
# Añadir la variable de entorno para el linker
ENV LD_LIBRARY_PATH=/usr/local/lib

# Descargar e instalar Geant4 v10.3.0
RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v10.3.0/geant4-v10.3.0.tar.gz \
    && tar -zxf geant4-v10.3.0.tar.gz \
    && mkdir geant4-v10.3.0-build && cd geant4-v10.3.0-build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local/geant4/10.3.0 \
             -DGEANT4_INSTALL_DATA=ON \
             -DGEANT4_USE_QT=ON \
             ../geant4-v10.3.0 \
    && make -j$(nproc) \
    && make install \
    && cd .. \
    && rm -rf geant4-v10.3.0 \
    && rm geant4-v10.3.0.tar.gz
    
# Configurar el entorno para Geant4
ENV GEANT4_DIR=/usr/local/geant4/10.3.0
ENV PATH=${GEANT4_DIR}/bin:${PATH}
ENV LD_LIBRARY_PATH=${GEANT4_DIR}/lib:${LD_LIBRARY_PATH}

# Punto de entrada o comando predeterminado
CMD ["/bin/bash"]
