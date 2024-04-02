//Archivos de cabecera que tienen que ser creados por el usuario
#include "DetectorConstruction.hh" //Define cómo se construye el mundo de la simualción y los detectores.
#include "PhysicsList.hh" // Especifica las leyes físicas que se aplicarán.
#include "ActionInitialization.hh" // Configura las acciones que se realizarán, como la generación de partículas primarias.

//Archivos que se encuentran en la carpeta include del directorio de instalación. Proporcionan funcionalidades para gestionar la simulación y la interfaz de usuario.
#include "G4RunManager.hh"
#include "G4UImanager.hh"

//la función main() es el punto de entrada de cualquier programa en C++. Cuando ejecutas un programa, el sistema operativo invoca esta función para comenzar la ejecución del código. Dentro de main() defines todas las operaciones que tu programa realizará. Todo lo que se incluya en main() será parte de la ejecución del programa. Esta función es el único punto de entrada reconocido para la ejecución de un programa en C++.
int main() {
    // Construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    // Initialize G4 kernel
    runManager->Initialize();

    // Get the pointer to the UI manager and set verbosities
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->ApplyCommand("/tracking/verbose 1");

    // Start a run
    int numberOfEvent = 3;
    runManager->BeamOn(numberOfEvent);

    // Job termination
    delete runManager;
    return 0;
}

