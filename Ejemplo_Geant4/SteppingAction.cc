// SteppingAction.cc
#include "SteppingAction.hh"
#include "G4Step.hh"

SteppingAction::SteppingAction()
: G4UserSteppingAction()
{ }

SteppingAction::~SteppingAction()
{ }

void SteppingAction::UserSteppingAction(const G4Step* step)
{
   // Aquí puedes añadir código para hacer algo en cada paso de la simulación
   // Por ejemplo, puedes imprimir la energía depositada en este paso con:
   // G4double edep = step->GetTotalEnergyDeposit();
}
