#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "MyDetectorConstruction.hh"



ActionInitialization::ActionInitialization(MyDetectorConstruction* detectorConstruction)
 : G4VUserActionInitialization(),
   parCrk(new PrimarySpectrum()), fDetectorConstruction(detectorConstruction)
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

    // Crear y configurar RunAction con el detector sensible
    RunAction* runAction = new RunAction(fDetectorConstruction);
    SetUserAction(runAction);

    // Configura la acción de run con el detector sensible
    //RunAction* runAction = new RunAction(fSensitiveDetector);
    //SetUserAction(runAction);
    
    //MySteppingAction* steppingAction = new MySteppingAction();
    //SetUserAction(steppingAction);
    
    //RunAction* runAction = new RunAction();
    //SetUserAction(runAction);
}
