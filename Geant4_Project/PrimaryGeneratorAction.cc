// Geant4 Libraries
//
#include "Randomize.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

// Local Libraries
//
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "PrimarySpectrum.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(PrimarySpectrum* crkPart)
  : G4VUserPrimaryGeneratorAction(), 
    fCrkPar(crkPart),
    fParticleGun(0)
{
  G4cout << "...PrimaryGeneratorAction..." << G4endl;

  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // Create a messenger for this class
  fGunMessenger = new PrimaryGeneratorMessenger(this);

  // Default kinematic (commented out as per original code)
  /*
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  primaryId = "mu-";
  G4ParticleDefinition* particle = particleTable->FindParticle(primaryId);
  fParticleGun->SetParticleDefinition(particle);
  */
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Update primary particle properties from the PrimarySpectrum object
  fCrkPar->primaryPosition(); // Esta función no hace nada.
  fCrkPar->primaryMomento();

  position = fCrkPar->particlePosition;
  direction = fCrkPar->particleDirection;
  primaryId = fCrkPar->parId;

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle(primaryId);

  if (!particle)
  {
    G4cerr << "Particle " << primaryId << " not found!" << G4endl;
    return;
  }

  fParticleGun->SetParticleDefinition(particle);
  G4cout << "La partícula es: " << particle << G4endl;
  fParticleGun->SetParticlePosition(position);
  G4cout << "La posición de la partícula es: " << position << G4endl;
  fParticleGun->SetParticleMomentumDirection(direction);
  G4cout << "La momento de la partícula es: " << direction << G4endl;
  fParticleGun->SetParticleEnergy(fCrkPar->getEnergy());

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::SetOptPhotonPolar()
{
  G4double angle = G4UniformRand() * 360.0 * deg;
  SetOptPhotonPolar(angle);
}

void PrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
  if (fParticleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
  {
    G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar(): "
              "the particleGun is not an opticalphoton" << G4endl;
    return;
  }

  G4ThreeVector normal(1., 0., 0.);
  G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
  G4ThreeVector product = normal.cross(kphoton);
  G4double modul2 = product * product;

  G4ThreeVector e_perpend(0., 0., 1.);
  if (modul2 > 0.) e_perpend = (1. / std::sqrt(modul2)) * product;
  G4ThreeVector e_paralle = e_perpend.cross(kphoton);

  G4ThreeVector polar = std::cos(angle) * e_paralle + std::sin(angle) * e_perpend;
  fParticleGun->SetParticlePolarization(polar);
}

