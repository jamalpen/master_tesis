# Usar una imagen base de Ubuntu
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
	qtbase5-dev \
	qtchooser \
	qt5-default \
	qt5-qmake \
	qtbase5-dev-tools \
	libglu1-mesa-dev \
	libgl1-mesa-dev \
	libx11-dev \
	libxmu-dev \
	libxi-dev \
	libmotif-dev \
	wget \
	mesa-utils \
	libgl1-mesa-glx \
	libgl1-mesa-dri \
	&& rm -rf /var/lib/apt/lists/*
	
# Establecer el directorio de trabajo en /home
WORKDIR /home/software
	
# Descargar e instalar Xerces-C
RUN wget https://archive.apache.org/dist/xerces/c/3/sources/xerces-c-3.2.3.tar.gz \
	&& tar -zxf xerces-c-3.2.3.tar.gz \
	&& cd xerces-c-3.2.3 \
	&& ./configure \
	&& make -j4 \
	&& make install \
	&& cd .. \
	&& rm -rf xerces-c-3.2.3.tar.gz
	
# Descargar e instalar Geant4 v10.3.0
RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v10.3.0/geant4-v10.3.0.tar.gz \
	&& mkdir geant4 && cd geant4 \
	&& tar xzfv /home/software/geant4-v10.3.0.tar.gz \
	&& mkdir geant4-v10.3.0-build && cd geant4-v10.3.0-build \
	&& cmake -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_RAYTRACER_X11=ON -DGEANT4_USE_SYSTEM_EXPAT=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_GDML=ON -DGEANT4_BUILD_MULTITHREADED=ON -DCMAKE_INSTALL_PREFIX=/home/software/geant4/geant4-v10.3.0-install /home/software/geant4/geant4-v10.3.0 \
	&& make -j4 \
	&& make install \
	&& cd .. \
	&& cd .. \
	&& rm -rf geant4-v10.3.0.tar.gz
	
# Añadir la variable de entorno para el linker
ENV LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:/home/software/geant4/geant4-v10.3.0-install/lib

# Configurar el entorno para Geant4
ENV GEANT4_DIR=/home/software/geant4/geant4-v10.3.0-install
ENV PATH=${GEANT4_DIR}/bin:${PATH}
ENV LD_LIBRARY_PATH=${GEANT4_DIR}/lib:${LD_LIBRARY_PATH}

# Punto de entrada o comando predeterminado
CMD ["/bin/bash"]
