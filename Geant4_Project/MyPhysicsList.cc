#include "MyPhysicsList.hh"
//#include "ExtraPhysics.hh"

MyPhysicsList::MyPhysicsList(G4String physName)
{
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
