#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "detector.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction();

    virtual void EndOfRunAction(const G4Run* run);
};

#endif

