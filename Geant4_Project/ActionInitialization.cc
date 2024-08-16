#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"



ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization(),
   parCrk(new PrimarySpectrum())
{
    G4cout << "...ActionInitialization..." << G4endl;
}

ActionInitialization::~ActionInitialization()
{
    // delete parCrk;
}

void ActionInitialization::Build() const
{
    PrimaryGeneratorAction* primaryGenAction = new PrimaryGeneratorAction(parCrk);
    SetUserAction(primaryGenAction);
    
    //MySteppingAction* steppingAction = new MySteppingAction();
    //SetUserAction(steppingAction);
    
    //RunAction* runAction = new RunAction();
    //SetUserAction(runAction);
}
