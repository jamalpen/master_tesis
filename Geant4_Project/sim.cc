// Geant4 Libraries
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"

#include "MyDetectorConstruction.hh"
#include "MyPhysicsList.hh"
#include "ActionInitialization.hh"

#include "PrimarySpectrum.hh"

// C++ Libraries
#include "Randomize.hh"
#include <iostream>

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " OpNovic [-m macro ] [-u UIsession] [-t nThreads] [-r seed] "
           << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

int main(int argc, char** argv) {
    
    // Initial debug message
    G4cout << "Starting Geant4 program..." << G4endl;

    // Prueba del método openfile de PrimarySpectrum
    PrimarySpectrum* james1 = new PrimarySpectrum();
    int james = james1->openFile("particle.shw.bz2");
    std::cout << "El valor del numero es: " << james << std::endl;
    
    
    //Prueba del método primaryMomento
    james1->primaryMomento();
    double energia = james1->getEnergy();
    std::cout << "El valor de la energia es: " << energia << std::endl;
    james1->primaryMomento();
    double energia1 = james1->getEnergy();
    std::cout << "El valor de la energia es: " << energia1 << std::endl;
    james1->primaryMomento();
    double energia2 = james1->getEnergy();
    std::cout << "El valor de la energia es: " << energia2 << std::endl;
    


    // Evaluate arguments
    if ( argc > 9 ) {
      PrintUsage();
      return 1;
    }

    G4String macro;
    G4String session;
    #ifdef G4MULTITHREADED
      G4int nThreads = 0;
      G4cout << "Multithreading support enabled." << G4endl;
    #else
      G4cout << "Multithreading support NOT enabled." << G4endl;
    #endif

    G4long myseed = time(NULL);

    for ( G4int i=1; i<argc; i=i+2 ){
      if      ( G4String(argv[i]) == "-m" ) macro   = argv[i+1];
      else if ( G4String(argv[i]) == "-u" ) session = argv[i+1]; 
      else if ( G4String(argv[i]) == "-r" ) myseed  = atoi(argv[i+1]);
    #ifdef G4MULTITHREADED
      else if ( G4String(argv[i]) == "-t" ){
          nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
          G4cout << "Number of threads set to: " << nThreads << G4endl;
      }
    #endif
      else {
          PrintUsage();
          return 1;
      }
    }

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4cout << "Random engine configured." << G4endl;

    // Create the G4RunManager object with multithreading support if enabled
    #ifdef G4MULTITHREADED
      G4MTRunManager *runManager = new G4MTRunManager();
      G4cout << "G4MTRunManager created (multithreading support)." << G4endl;
      if ( nThreads > 0 ) runManager->SetNumberOfThreads(nThreads); 
    #else
      G4RunManager *runManager = new G4RunManager();
      G4cout << "G4RunManager created (no multithreading support)." << G4endl;
    #endif

    // Seed the random number generator manually
    G4Random::setTheSeed(myseed);
    G4cout << "Seed set to: " << myseed << G4endl;

    G4String physName = "QGSP_BERT_HP";

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList(physName));
    runManager->SetUserInitialization(new ActionInitialization());


    // Initialize G4 kernel
    runManager->Initialize();

    // Visualization manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if ( macro.size() ) {
      // Batch mode
      G4String command = "/control/execute ";
      UImanager->ApplyCommand(command+macro);
      //UImanager->ApplyCommand("/vis/open OGL");
    } else { 
      // Define UI session for interactive mode
      G4UIExecutive * ui = new G4UIExecutive(argc, argv, session);
      UImanager->ApplyCommand("/control/execute vis.mac");
      //UImanager->ApplyCommand("/control/execute input.in");
      if (ui->IsGUI()){
        UImanager->ApplyCommand("/control/execute gui.mac");
      } else {
        G4cout << "IsGUI() returned false: NO GUI session detected." << G4endl;
      }
      ui->SessionStart();
      delete ui;
    }

    delete visManager;
    delete runManager;
    
    return 0;
}