# Geant4 container

First, create a working directory on your local computer:

```
cd
mkdir Geant4_Simulations
chmod -R 777 Geant4_Simulations
```

Then, download the Geant4 container and start it with the docker run command.

If you are on native Linux and want to use X11-forwarding, use

```bash
docker run -it --env="LIBGL_ALWAYS_SOFTWARE=1"  --name my_geant4   --net=host   --env="DISPLAY" --device /dev/dri  -v $HOME/.Xauthority:/root/.Xauthority:rw   -v ${HOME}/Geant4_Simulations:/home/geant4lab/Geant4_projects   jpenafiell/geant4-v10.3.0:1.1
```

If you want to use the graphical user interface (GUI) capabilities of the Geant4 application running inside this container on a Linux system, you will need to allow the X server on your Linux host machine to accept connections from that container. By default, the X server is set up to reject these connections for security reasons. However, you can override this setting to enable your Geant4 GUI to display on the host's screen. To do so, try typing the following before starting your Docker container.

```bash
xhost +local:root
```

Now let's understand the options that were used for the docker run command

* First, the `-it` option means to start the container in interactive mode. Essentially, you'll find yourself within the environment of the container.

*******Complete this section later********

To streamline the initialization of a Geant4 program within this specific container, the traditional method of executing a lengthy command to set up the environment has been simplified. Traditionally, one would need to run the following command:

```bash
source /home/geant4lab/geant4/geant4-v10.3.0-install/share/Geant4-10.3.0/geant4make/geant4make.sh
```

However, in this container, the setup process has been made more efficient. Instead of executing the above command, users only need to enter the following command inside the container:

```bash
g4make
```

This single command is sufficient for preparing the container for the initialization of a Geant4 program. This simplification enhances user convenience and accelerates the process of getting started with Geant4 projects within this container.
