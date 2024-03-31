// PrimaryGeneratorAction.cc
#include "PrimaryGeneratorAction.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(new G4ParticleGun(1))
{
   // Default particle kinematic
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   G4String particleName = "proton";
   G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
   fParticleGun->SetParticleDefinition(particle);
   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
   fParticleGun->SetParticleEnergy(100.*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
   delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   fParticleGun->GeneratePrimaryVertex(anEvent);
}
