#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "RunAction.hh"

#include "PrimarySpectrum.hh"
#include "MyDetectorConstruction.hh" 


// class B4DetectorConstruction;
class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization(MyDetectorConstruction* detectorConstruction);
    virtual ~ActionInitialization();

    virtual void Build() const;
    //virtual void EndOfRunAction(const G4Run* run); // Añade este método

private:
    PrimarySpectrum* parCrk;
    MyDetectorConstruction* fDetectorConstruction;
};

#endif

