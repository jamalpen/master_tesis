#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "globals.hh"
#include "MyDetectorConstruction.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction(MyDetectorConstruction* detectorConstruction);
    ~RunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    MyDetectorConstruction* fDetectorConstruction;

};

#endif