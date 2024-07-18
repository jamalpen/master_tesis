#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"
#include "PrimaryGeneratorAction.hh"

// Class to initialize user actions
class ActionInitialization : public G4VUserActionInitialization
{
public:
    // Constructor
    ActionInitialization();
    // Destructor
    virtual ~ActionInitialization();

    // Method to build actions for the master thread
    virtual void BuildForMaster() const;
    // Method to build actions for worker threads
    virtual void Build() const;

    // Method to add particle from external source
    void AddParticle(G4ParticleDefinition* particleDef, G4ThreeVector position, G4ThreeVector momentum, G4double energy);

private:
    // Pointer to primary generator action
    mutable PrimaryGeneratorAction* fPrimaryGeneratorAction; // Declare as mutable to allow modification in const methods
};

#endif
