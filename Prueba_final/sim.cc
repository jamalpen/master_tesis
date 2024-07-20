// Geant4 Libraries
//
#include "G4RunManager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "G4UImanager.hh"

// C++ Libraries
//
#include "Randomize.hh"

// Local Libraries
//
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " OpNovic [-m macro ] [-u UIsession] [-r seed] " << G4endl;
  }
}

int main(int argc, char** argv)
{
  // Evaluate arguments
  if (argc > 7) {
    PrintUsage();
    return 1;
  }

  G4String macro;
  G4String session;
  G4long myseed = time(NULL);

  for (G4int i = 1; i < argc; i = i + 2) {
    if (G4String(argv[i]) == "-m") macro = argv[i + 1];
    else if (G4String(argv[i]) == "-u") session = argv[i + 1];
    else if (G4String(argv[i]) == "-r") myseed = atoi(argv[i + 1]);
    else {
      PrintUsage();
      return 1;
    }
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Seed the random number generator manually
  G4Random::setTheSeed(myseed);
  G4cout << "myseed: " << myseed << G4endl;

  G4String physName = "QGSP_BERT_HP";

  // Set mandatory initialization classes
  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList(physName));
  runManager->SetUserInitialization(new ActionInitialization());

  // Initialize G4 kernel
  runManager->Initialize();

#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (macro.size()) {
    // Batch mode
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command + macro);
  } else {
    // Define UI session for interactive mode
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv, session);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
    UImanager->ApplyCommand("/control/execute input.in");
#endif
    if (ui->IsGUI())
      UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
#endif
  }

  // Job termination
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

