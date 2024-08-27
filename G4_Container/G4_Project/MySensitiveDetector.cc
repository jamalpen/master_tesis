#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


#include "MySensitiveDetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) 
    : G4VSensitiveDetector(name), particleCount(0)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4cout << "Dirección en ProcessHits: " << this << G4endl;

    // Obtener la pista de la partícula
    G4Track *track = aStep->GetTrack();

    // Obtener los puntos de paso de la partícula
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
    
    //G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4ThreeVector posParticulainicial = preStepPoint->GetPosition(); // los valores están en mm. Recuerda que Geant4 entrega valores por defecto en mm.
    G4ThreeVector posParticulafinal = postStepPoint->GetPosition();

    //G4cout << "Esta partícula ha tocado el detector" << G4endl;
    G4cout << "Posición inicial de la partícula es: " << posParticulainicial << G4endl;
    G4cout << "Posición final de la partícula es: " << posParticulafinal << G4endl; 

    // Imprimir la posición de la partícula en el detector
    //G4cout << "Posicion de la partícula en el detector: " << posPhoton << G4endl;

     // Incrementar el contador de partículas
    particleCount++;

    // Imprimir el contador de partículas al final del evento o cuando quieras
    G4cout << "Número total de partículas que han entrado al detector: " << particleCount << G4endl;
    
    // Detener y eliminar la pista de la partícula
    track->SetTrackStatus(fStopAndKill);

    // Devolver true para indicar que el hit fue procesado exitosamente
    return true;
}

G4int MySensitiveDetector::GetParticleCount() const
{
    //G4cout << "Particle count is: " << particleCount << G4endl;
    //G4cout << "Dirección en GetParticleCount: " << this << G4endl;
    return particleCount;
}
