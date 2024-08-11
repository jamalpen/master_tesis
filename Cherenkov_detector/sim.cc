#include <iostream>
// Include the standard input/output library for basic operations

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
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
    
    G4UIExecutive *ui = 0;
    
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif
    
    
    // Create an instance of G4RunManager to manage the simulation
    
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());      
    
    
    if(argc == 1){
    
         ui = new G4UIExecutive(argc, argv);
    
    }
    
    
    // Create an instance of G4UIExecutive to manage the user interface session, using command line arguments
    
    G4VisManager *visManager = new G4VisExecutive();
    // Create an instance of G4VisExecutive to manage visualization
    visManager->Initialize();
    // Initialize the visualization manager
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // Get a pointer to the singleton instance of G4UImanager to manage UI commands
    
    if(ui){
        
          UImanager->ApplyCommand("/control/execute vis.mac");

          ui->SessionStart();
          // Start the UI session, allowing interactive commands to be processed
    
    }
    
    else{
          
          G4String command = "/control/execute ";
          G4String fileName = argv[1];
          UImanager->ApplyCommand(command+fileName);
    
    }
    
    

    
    return 0;    
    // Return 0 to indicate successful execution
}

