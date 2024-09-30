#include "RunAction.hh"
#include "MySensitiveDetector.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(MyDetectorConstruction* detectorConstruction)
    : G4UserRunAction(), fDetectorConstruction(detectorConstruction)
{
    // Constructor: Aquí puedes inicializar variables o realizar configuraciones iniciales

    // Open the output file
    outFile.open("simulation_results.txt", std::ios::app);  // Append mode

    if (!outFile.is_open()) {
        G4cerr << "Error: Could not open output file." << G4endl;
    }

    startTime = 0;
    endTime = 0;
}

RunAction::~RunAction()
{
    // Destructor: Libera cualquier recurso si es necesario
    // Close the output file if it's open
    if (outFile.is_open()) {
        outFile.close();
    }
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    // Este método se ejecuta al inicio de cada run

    G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

    // Aquí puedes inicializar variables, abrir archivos de salida, etc.
    // Por ejemplo, podrías resetear el contador de partículas si fuera necesario

    // Record the start time of the simulation
    startTime = std::clock();
}


void RunAction::EndOfRunAction(const G4Run* run)
{
    // Este método se ejecuta al final de cada run

    // Measure end time
    endTime = std::clock();
    
    // Calculate simulation time
    double simulationTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    
    MySensitiveDetector* sensitiveDetector = fDetectorConstruction->GetSensitiveDetector();

    // Imprimir el número total de partículas detectadas
    if (sensitiveDetector)
    {
        G4cout << "Detector sensible correctamente inicializado en RunAction." << G4endl;
        G4cout << "Número total de partículas detectadas: "
               << sensitiveDetector->GetParticleCount() << G4endl;
    }
    else
    {
        G4cout << "No se ha detectado ninguna partícula." << G4endl;
    }

    // Aquí también puedes guardar resultados en un archivo, cerrar archivos, etc.

    // Obtener los valores del campo magnético
    G4ThreeVector magneticField = fDetectorConstruction->GetMagneticFieldValue();

    G4cout << "### Run " << run->GetRunID() << " end." << G4endl;

    // Escribir los valores en el archivo de salida
    if (outFile.is_open())
    {
        outFile << "### Run " << run->GetRunID() << " ###\n";
        outFile << "Magnetic Field (X): " << magneticField.x() / tesla << " T\n";
        outFile << "Magnetic Field (Y): " << magneticField.y() / tesla << " T\n";
        outFile << "Magnetic Field (Z): " << magneticField.z() / tesla << " T\n";
        outFile << "Simulation time: " << simulationTime << " seconds\n";
        outFile << "Particles detected: " << sensitiveDetector->GetParticleCount() << "\n";
        outFile << "Particles simulated: " << run->GetNumberOfEventToBeProcessed() << "\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile << "---------------------------------------\n";
        outFile.close();
    } else {
        G4cerr << "Error: Could not open output file." << G4endl;
    }
}