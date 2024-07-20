#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv) {
    std::cout << "Initializing run manager..." << std::endl;
    G4RunManager* runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    std::cout << "Initializing Geant4 kernel..." << std::endl;
    runManager->Initialize();

    std::cout << "Initializing visualization manager..." << std::endl;
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc == 2) {
        std::cout << "Running in batch mode..." << std::endl;
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + argv[1]);
    } else {
        std::cout << "Running in interactive mode..." << std::endl;
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        std::cout << "Executing vis.mac..." << std::endl;
        UImanager->ApplyCommand("/control/execute vis.mac");
        std::cout << "Executing input.in..." << std::endl;
        UImanager->ApplyCommand("/control/execute input.in");
        std::cout << "Starting UI session..." << std::endl;
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;

    std::cout << "Simulation finished successfully." << std::endl;
    return 0;
}

