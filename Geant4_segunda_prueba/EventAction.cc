#include "EventAction.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"

// Constructor
EventAction::EventAction()
: G4UserEventAction()
{ }

// Destructor
EventAction::~EventAction()
{ }

// Method called at the beginning of each event
void EventAction::BeginOfEventAction(const G4Event*)
{
   // Code to execute at the beginning of each event, e.g., initializing counters
}

// Method called at the end of each event
void EventAction::EndOfEventAction(const G4Event* event)
{
    // More custom output or operations using event
    // No custom output here
}

