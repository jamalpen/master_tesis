#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"

// EventAction class inheriting from G4UserEventAction
class EventAction : public G4UserEventAction
{
public:
    // Constructor
    EventAction();

    // Destructor
    virtual ~EventAction();

    // Method called at the beginning of each event
    virtual void BeginOfEventAction(const G4Event*);

    // Method called at the end of each event
    virtual void EndOfEventAction(const G4Event* event);
};

#endif
