## CORSIKA-arti container

First, create a working directory on your local computer:

```
cd
mkdir CORSIKA_Simulations
chmod -R 777 CORSIKA_Simulations
```

Second, pull the CORSIKA-arti image from DockerHub

```bash
docker pull jpenafiell/corsika:latest
```

Then, to create the container, use

```bash
docker run -it -v ${HOME}/CORSIKA_Simulations/:/home/ --name my_arti jpenafiell/corsika:latest
```

Before running a simulation inside the container, make sure to first edit the `datos.txt` file.

```bash
# Time (seconds) / Height (meters) / Distance (kilometers) / Zenith angle (degrees) / Max Zenith angle (degrees)
100     2200    10      88      90
100	2200	10	88	90
```

In the `datos.txt` file, you can list all the simulations you need to run, with each simulation on a separate line. Then, execute the following:

```bash
./integrated_run.sh
```

## ⚠️ Warning

If the simulation does not execute effectively, files may be generated in the `/opt/corsika-77402/run` directory. To remove them, run the following command:

```bash
./cleanup_simulation_data.sh <theta> <thetamax> <time>
```

The command above requires 3 mandatory parameters. The first parameter represents the minimum zenith angle for your simulation, the second determines the maximum zenith angle, and the third specifies the simulation time.

Este es un comentario para ti James, resulta que el comando de arriba solo borra los archivos que comienzan con go pero no los que comienzan con run, por favor no olvidar de añadir que también borre esos archivos que comienzan con run y que no se ejecutan por que fallo la simulación.









