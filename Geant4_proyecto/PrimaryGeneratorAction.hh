#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include <vector>

// Class to handle the primary particle generation
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    // Constructor
    PrimaryGeneratorAction();
    // Destructor
    virtual ~PrimaryGeneratorAction();

    // Method called to generate primary particles for each event
    virtual void GeneratePrimaries(G4Event*);

    // Method to add particle data
    void AddParticle(G4ParticleDefinition* particleDef, G4ThreeVector position, G4ThreeVector momentum, G4double energy);

private:
    // Particle gun to generate particles
    G4ParticleGun* fParticleGun;
    
    // Struct to hold particle data
    struct ParticleData {
        G4ParticleDefinition* definition; // Particle definition
        G4ThreeVector position;           // Position of the particle
        G4ThreeVector momentum;           // Momentum direction of the particle
        G4double energy;                  // Energy of the particle
    };
    // Vector to store multiple particles
    std::vector<ParticleData> fParticleData;
};

#endif
