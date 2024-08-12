#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


int main(int argc, char** argv) {
    
    //Create the user interface
    /*Assigning a pointer to 0 is equivalent to assigning it to nullptr, it means
    that ui does not point to a G4UIExecutive object*/
    G4UIExecutive *ui = 0;
    
    //Create the G4RunManager object
    G4RunManager *runManager = new G4RunManager();
    //Initialize the runManager
    //runManager->Initialize(); 
    
    //hola bebe

    //if conditions
    
    if(argc == 1){
    
         ui = new G4UIExecutive(argc, argv);
    
    }
    
    
    //Visualization manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
    /*if(ui) condition means that ui is different from 0*/
    if(ui){
        
          //UImanager->ApplyCommand("/control/execute vis.mac");

          ui->SessionStart();
          // Start the UI session, allowing interactive commands to be processed
    }
    
    else{
          
          G4String command = "/control/execute ";
          G4String fileName = argv[1];
          UImanager->ApplyCommand(command+fileName);
    }
    
    return 0;
}

