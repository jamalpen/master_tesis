// PhysicsList.hh
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:
   PhysicsList();
   virtual ~PhysicsList();

protected:
   // Set default cut value for secondary particles
   virtual void SetCuts();
};

#endif
