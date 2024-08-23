#include "RunAction.hh"
#include "MySensitiveDetector.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(MyDetectorConstruction* detectorConstruction)
    : G4UserRunAction(), fDetectorConstruction(detectorConstruction)
{
    // Constructor: Aquí puedes inicializar variables o realizar configuraciones iniciales
}

RunAction::~RunAction()
{
    // Destructor: Libera cualquier recurso si es necesario
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    // Este método se ejecuta al inicio de cada run

    G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

    // Aquí puedes inicializar variables, abrir archivos de salida, etc.
    // Por ejemplo, podrías resetear el contador de partículas si fuera necesario
}


void RunAction::EndOfRunAction(const G4Run* run)
{
    // Este método se ejecuta al final de cada run

    G4cout << "### Run " << run->GetRunID() << " end." << G4endl;
    
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
}