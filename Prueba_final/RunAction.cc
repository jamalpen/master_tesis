#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

RunAction::RunAction() : G4UserRunAction()
{}

RunAction::~RunAction()
{}

void RunAction::EndOfRunAction(const G4Run* run)
{
    // Obtener el detector sensible
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    MySensitiveDetector* sensDet = (MySensitiveDetector*)sdManager->FindSensitiveDetector("SensitiveDetector");

    // Obtener el conteo de partículas
    if (sensDet) {
        G4int particleCount = sensDet->GetParticleCount();
        G4cout << "Número de partículas en el detector fantasma: " << particleCount << G4endl;
    }else {
        G4cerr << "SensitiveDetector is not found!" << G4endl;
    }
}

