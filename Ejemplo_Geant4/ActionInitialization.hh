// ActionInitialization.hh
#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
   ActionInitialization();
   virtual ~ActionInitialization();

   virtual void Build() const;
   virtual void BuildForMaster() const;
};

#endif
