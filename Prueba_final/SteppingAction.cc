#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"

MySteppingAction::MySteppingAction():lastPosition(G4ThreeVector()), minDistance(1.0 * m) // Configura la distancia mínima
{}
MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4ThreeVector pos = preStepPoint->GetPosition();
    
    // Calcular la distancia recorrida desde la última posición registrada
    //G4double distance = (pos - lastPosition).mag();

    // Convert position from mm to meters
    //G4ThreeVector posInMeters = pos / m;

    // G4cout << "Step position in meters: " << posInMeters << G4endl;
}

