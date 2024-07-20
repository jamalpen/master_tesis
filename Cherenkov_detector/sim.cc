#include <iostream>
// Include the standard input/output library for basic operations

#include "G4RunManager.hh"
// Include the header for G4RunManager, which manages the simulation run

#include "G4UImanager.hh"
// Include the header for G4UImanager, which manages user interface commands

#include "G4VisManager.hh"
// Include the header for G4VisManager, the base class for visualization managers

#include "G4VisExecutive.hh"
// Include the header for G4VisExecutive, the concrete implementation of G4VisManager

#include "G4UIExecutive.hh"
// Include the header for G4UIExecutive, which manages the user interface session

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv) {
    // Define the main function with command line arguments
    
    G4RunManager *runManager = new G4RunManager();
    // Create an instance of G4RunManager to manage the simulation
    
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    runManager->Initialize();
    
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    // Create an instance of G4UIExecutive to manage the user interface session, using command line arguments
    
    G4VisManager *visManager = new G4VisExecutive();
    // Create an instance of G4VisExecutive to manage visualization
    visManager->Initialize();
    // Initialize the visualization manager
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // Get a pointer to the singleton instance of G4UImanager to manage UI commands
    
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    
    
    
    ui->SessionStart();
    // Start the UI session, allowing interactive commands to be processed
    
    return 0;    
    // Return 0 to indicate successful execution
}

