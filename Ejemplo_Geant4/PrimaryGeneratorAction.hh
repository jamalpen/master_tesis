// PrimaryGeneratorAction.hh
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
   PrimaryGeneratorAction();
   virtual ~PrimaryGeneratorAction();

   virtual void GeneratePrimaries(G4Event* anEvent);

private:
   G4ParticleGun* fParticleGun;  // The particle gun
};

#endif
