#ifndef PrimaryGeneratorAction_HH
#define PrimaryGeneratorAction_HH

// Geant Libraries
//
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

// Local Libraries
//
#include "PrimarySpectrum.hh"

// C++ Libraries
//
#include <string>

class G4ParticleGun;
class G4Event;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction(PrimarySpectrum* crkPart);
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);

    PrimarySpectrum* fCrkPar;

    std::string primaryId;
    G4ThreeVector position;
    G4ThreeVector direction;

private:
    G4ParticleGun* fParticleGun;
    PrimaryGeneratorMessenger* fGunMessenger;
};

#endif

