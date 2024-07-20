///////////////////////////////////
////////PrimarySpectrum.hh/////////
///////////////////////////////////

#ifndef PrimarySpectrumMessenger_h
#define PrimarySpectrumMessenger_h 1

// Geant4 Libraries
#include "G4UImessenger.hh"
#include "globals.hh"

class PrimarySpectrum;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class PrimarySpectrumMessenger : public G4UImessenger
{
public:
    PrimarySpectrumMessenger(PrimarySpectrum* spectrum);
    virtual ~PrimarySpectrumMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    PrimarySpectrum* fSpectrum;
    G4UIdirectory* fSpecDir;

    G4UIcmdWithAString* inFile;
    G4UIcmdWithADoubleAndUnit* xInit;
    G4UIcmdWithADoubleAndUnit* yInit;
    G4UIcmdWithADoubleAndUnit* zInit;
    G4UIcmdWithADoubleAndUnit* areaDimX;
    G4UIcmdWithADoubleAndUnit* areaDimY;
    G4UIcmdWithADoubleAndUnit* areaDimZ;
};

#endif
