#ifndef MYPHYSICSLIST_HH
#define MYPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList(G4String);
    ~MyPhysicsList();
};

#endif
