#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

// Constructor
RunAction::RunAction()
: G4UserRunAction()
{ }

// Destructor
RunAction::~RunAction()
{ }

// Method called at the beginning of each run
void RunAction::BeginOfRunAction(const G4Run*)
{
   // Code to execute at the start of each run, e.g., opening data files
}

// Method called at the end of each run
void RunAction::EndOfRunAction(const G4Run*)
{
   // Code to execute at the end of each run, e.g., closing data files
}
