#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

// Constructor
ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization(), fPrimaryGeneratorAction(nullptr) {}

// Destructor
ActionInitialization::~ActionInitialization() {
    delete fPrimaryGeneratorAction; // Clean up memory to avoid leaks
}

// Method to build actions for the master thread
void ActionInitialization::BuildForMaster() const {
    // Set user action classes for the master thread
    SetUserAction(new RunAction());
}

// Method to build actions for worker threads
void ActionInitialization::Build() const {
    // Initialize the primary generator action if not already done
    if (!fPrimaryGeneratorAction) {
        fPrimaryGeneratorAction = new PrimaryGeneratorAction();
    }
    SetUserAction(fPrimaryGeneratorAction);

    // Set other user actions
    SetUserAction(new RunAction());
    SetUserAction(new EventAction());
    SetUserAction(new SteppingAction());
}

// Method to add particle from external source
void ActionInitialization::AddParticle(G4ParticleDefinition* particleDef, G4ThreeVector position, G4ThreeVector momentum, G4double energy) {
    // If primary generator action is created, add the particle to it
    if (fPrimaryGeneratorAction) {
        fPrimaryGeneratorAction->AddParticle(particleDef, position, momentum, energy);
    }
}
