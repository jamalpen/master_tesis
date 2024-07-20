#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "globals.hh" // Es el archivo de cabecera para G4double

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction();
    virtual ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);
    
private:
    G4ThreeVector lastPosition;
    G4double minDistance;
    
};

#endif

