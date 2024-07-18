// PhysicsList.cc
#include "PhysicsList.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
   SetVerboseLevel(1);
   
   // Standard EM Physics
   RegisterPhysics(new G4EmStandardPhysics());
   
   // Other physics processes and particles can be added here as needed
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::SetCuts()
{
   G4VUserPhysicsList::SetCuts();
   // Example of setting a cut for gamma
   SetCutValue(1*m, "gamma");
   SetCutValue(1*m, "e-");
   SetCutValue(1*m, "e+");
   SetCutValue(1*m, "proton");

   if (verboseLevel > 0) DumpCutValuesTable();
}
