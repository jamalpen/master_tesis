#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "PrimarySpectrum.hh"

// class B4DetectorConstruction;
class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void Build() const;
    //virtual void EndOfRunAction(const G4Run* run); // Añade este método

private:
    PrimarySpectrum* parCrk;
};

#endif

