#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"

// RunAction class inheriting from G4UserRunAction
class RunAction : public G4UserRunAction
{
public:
    // Constructor
    RunAction();

    // Destructor
    virtual ~RunAction();

    // Method called at the beginning of each run
    virtual void BeginOfRunAction(const G4Run*);

    // Method called at the end of each run
    virtual void EndOfRunAction(const G4Run*);
};

#endif
