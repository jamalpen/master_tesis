#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


#include "detector.hh" // Asegúrate de incluir el archivo de encabezado correcto

MySensitiveDetector::MySensitiveDetector(G4String name) 
    : G4VSensitiveDetector(name), particleCount(0)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    // Obtener la pista de la partícula
    G4Track *track = aStep->GetTrack();

    // Incrementar el contador de partículas
    particleCount++;

    // Detener y eliminar la pista de la partícula
    track->SetTrackStatus(fStopAndKill);

    // Obtener los puntos de paso de la partícula
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    // Imprimir la posición de la partícula en el detector
    //G4cout << "Posicion de la partícula en el detector: " << posPhoton << G4endl;

    // Devolver true para indicar que el hit fue procesado exitosamente
    return true;
}

G4int MySensitiveDetector::GetParticleCount() const
{
    return particleCount;
}
