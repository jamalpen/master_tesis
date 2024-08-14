#ifndef PrimaryGeneratorMessenger_HH
#define PrimaryGeneratorMessenger_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class PrimaryGeneratorMessenger : public G4UImessenger
{
public:
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
    virtual ~PrimaryGeneratorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

    void SetParticleMomentum(G4ThreeVector direction);

private:
    PrimaryGeneratorAction* fAction;

    G4UIdirectory* fGunDir;
    G4UIcmdWithADoubleAndUnit* fPolarCmd;
    G4UIcmdWithADoubleAndUnit* valueForTest;
};

#endif

