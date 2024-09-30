# Use Ubuntu base image
FROM ubuntu:20.04

# Avoid frontend questions during package installation
ARG DEBIAN_FRONTEND=noninteractive

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    cmake-curses-gui \
    gcc \
    g++ \
    libexpat1-dev \
    qtbase5-dev \
    qtchooser \
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
    nano \
    htop \
    && rm -rf /var/lib/apt/lists/*
    
# Set the working directory to /home
WORKDIR /home/geant4lab

# Download and install Xerces-C
RUN wget https://archive.apache.org/dist/xerces/c/3/sources/xerces-c-3.2.3.tar.gz \
    && tar -zxf xerces-c-3.2.3.tar.gz \
    && cd xerces-c-3.2.3 \
    && ./configure \
    && make -j4 \
    && make install \
    && cd .. \
    && rm -rf xerces-c-3.2.3.tar.gz \
    && rm -rf xerces-c-3.2.3
    
# Download and install Geant4 v10.7.3
RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v10.7.3/geant4-v10.7.3.tar.gz \
    && mkdir geant4 && cd geant4 \
    && tar xzfv /home/geant4lab/geant4-v10.7.3.tar.gz \
    && mkdir geant4-v10.7.3-build && cd geant4-v10.7.3-build \
    && cmake -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_RAYTRACER_X11=ON -DGEANT4_USE_SYSTEM_EXPAT=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_GDML=ON -DGEANT4_BUILD_MULTITHREADED=ON -DCMAKE_INSTALL_PREFIX=/home/geant4lab/geant4/geant4-v10.7.3-install /home/geant4lab/geant4/geant4-v10.7.3 \
    && make -j4 \
    && make install \
    && cd .. \
    && cd .. \
    && rm -rf geant4-v10.7.3.tar.gz
    
# Create the Geant4_projects directory
RUN mkdir /home/geant4lab/Geant4_projects

# Set the working directory to Geant4_projects
WORKDIR /home/geant4lab/Geant4_projects

# Create the alias g4make. This alias is used to avoid searching for the geant4make.sh file and executing the source geant4make.sh command in the directory containing this file.
RUN echo "alias g4make='cd /home/geant4lab/geant4/geant4-v10.7.3-install/share/Geant4-10.7.3/geant4make && source geant4make.sh && cd -'" >> /root/.bashrc

# Add environment variable for the linker
ENV LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:/home/geant4lab/geant4/geant4-v10.7.3-install/lib

# Configure the environment for Geant4
ENV GEANT4_DIR=/home/geant4lab/geant4/geant4-v10.7.3-install
ENV PATH=${GEANT4_DIR}/bin:${PATH}
ENV LD_LIBRARY_PATH=${GEANT4_DIR}/lib:${LD_LIBRARY_PATH}

# Copy the G4_project folder into the container
COPY G4_Project /home/geant4lab/Geant4_projects/G4_Project


# Install Google Cloud SDK (includes gsutil)
RUN apt-get update && apt-get install -y curl apt-transport-https ca-certificates gnupg \
  && echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://packages.cloud.google.com/apt cloud-sdk main" | tee -a /etc/apt/sources.list.d/google-cloud-sdk.list \
  && curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | apt-key --keyring /usr/share/keyrings/cloud.google.gpg add - \
  && apt-get update && apt-get install -y google-cloud-sdk

# Verify gsutil is installed
RUN gsutil version

# Entry point or default command
CMD ["/bin/bash"]
