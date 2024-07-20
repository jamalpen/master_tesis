#include "physics.hh"
//#include "ExtraPhysics.hh"

MyPhysicsList::MyPhysicsList(G4String physName)
{
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
    //RegisterPhysics(new ExtraPhysics());
    //RegisterPhysics(new G4DecayPhysics());
    //RegisterPhysics(new G4RadioactiveDecayPhysics());
    
    // Ajuste de los cortes de producción
    //SetCutValue(1.0 * mm, "gamma");
    //SetCutValue(1.0 * mm, "e-");
    //SetCutValue(1.0 * mm, "e+");
}

MyPhysicsList::~MyPhysicsList()
{}
