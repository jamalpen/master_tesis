#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

// Constructor
PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), fParticleGun(new G4ParticleGun(1)) 
{}

// Destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

// Method to generate primary particles for each event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
    if (fParticleData.empty()) {
        G4cerr << "No primary particles to generate." << G4endl;
        return;
    }
    
    G4cout << "Generating primary particles for event." << G4endl;
    // Loop over all stored particles and generate them
    for (const auto& particleData : fParticleData) {
        fParticleGun->SetParticleDefinition(particleData.definition);
        fParticleGun->SetParticleEnergy(particleData.energy);
        fParticleGun->SetParticlePosition(particleData.position);
        fParticleGun->SetParticleMomentumDirection(particleData.momentum);
        fParticleGun->GeneratePrimaryVertex(anEvent);
        
        G4cout << "Generated particle: " << particleData.definition->GetParticleName()
               << " with energy " << particleData.energy << " MeV" << G4endl;
    }
}

// Method to add particle data
void PrimaryGeneratorAction::AddParticle(G4ParticleDefinition* particleDef, G4ThreeVector position, G4ThreeVector momentum, G4double energy)
{
    ParticleData data = {particleDef, position, momentum, energy};
    fParticleData.push_back(data);
}
