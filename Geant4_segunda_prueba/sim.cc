#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

// Function to read parameters from input file
bool ReadInputFile(const std::string& filename, G4ThreeVector& dimensions, G4ThreeVector& particlePosition, G4String& unit, G4String& particleFilename) {
    std::ifstream infile(filename); // Open input file
    if (!infile) { // Check if file is opened successfully
        G4cerr << "Error: Cannot open file " << filename << G4endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) { // Read file line by line
        std::istringstream iss(line); // Create a string stream from the line
        std::string key;
        G4double x, y, z;
        std::string unit_str;
        if (iss >> key >> x >> y >> z >> unit_str) { // Extract key, coordinates, and unit from the line
            if (key == "/mydetector/worldDimensions") { // Check if key is for world dimensions
                if (unit_str == "km") { // Check if unit is kilometers
                    dimensions = G4ThreeVector(x*km, y*km, z*km); // Set dimensions
                } else {
                    G4cerr << "Error: Unrecognized unit for world dimensions" << G4endl;
                }
            } else if (key == "/mydetector/particlePosition") { // Check if key is for particle position
                if (unit_str == "m" || unit_str == "km") { // Check if unit is meters or kilometers
                    particlePosition = G4ThreeVector(x*(unit_str == "km" ? km : m), y*(unit_str == "km" ? km : m), z*(unit_str == "km" ? km : m)); // Set particle position
                } else {
                    G4cerr << "Error: Unrecognized unit for particle position" << G4endl;
                }
            } else if (key == "/mydetector/unit") { // Check if key is for unit
                unit = unit_str; // Set unit
            }
        } else if (key == "/spectrum/readfile") { // Check if key is for particle file
            iss >> particleFilename;
        }
    }

    return true; // Return true if file is read successfully
}

// Function to read particle data from a file
void ReadParticleFile(const std::string& filename, ActionInitialization* actionInitialization) {
    std::ifstream infile(filename); // Open particle file
    if (!infile) { // Check if file is opened successfully
        G4cerr << "Error: Cannot open particle file " << filename << G4endl;
        return;
    }

    G4cout << "Reading particle file: " << filename << G4endl;
    std::string line;
    int lineNumber = 0;

    while (std::getline(infile, line)) { // Read file line by line
        if (++lineNumber <= 5) continue; // Skip the first 5 lines

        std::istringstream iss(line); // Create a string stream from the line
        int particleID;
        double px, py, pz, x, y, z, energy, theta, phi;
        if (!(iss >> particleID >> px >> py >> pz >> x >> y >> z >> energy >> theta >> phi)) {
            G4cerr << "Error: Could not read line " << lineNumber << G4endl;
            continue;
        }

        G4ParticleDefinition* particleDef = nullptr;
        // Identify the particle type based on the ID
        switch (particleID % 100) {
            case 13:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("neutron"); // Neutron
                break;
            case 1:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("gamma"); // Gamma
                break;
            case 5:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("anti_muon"); // Anti-muon
                break;
            case 6:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("muon"); // Muon
                break;
            case 2:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("e+"); // Positron
                break;
            case 14:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("proton"); // Proton
                break;
            case 3:
                particleDef = G4ParticleTable::GetParticleTable()->FindParticle("e-"); // Electron
                break;
            default:
                G4cerr << "Unknown particle ID: " << particleID << G4endl; // Unknown particle
                continue;
        }

        G4ThreeVector position(x*m, y*m, z*m); // Position in meters
        G4ThreeVector momentum(px, py, pz); // Momentum direction

        G4cout << "Adding particle: ID=" << particleID << ", Position=" << position
               << ", Momentum=" << momentum << ", Energy=" << energy << " MeV" << G4endl;

        // Add particle to the action initialization
        actionInitialization->AddParticle(particleDef, position, momentum, energy*MeV);
    }
}

int main(int argc, char** argv) {
    // Default input filenames
    G4String inputFilename = "input.in"; // Default input filename for simulation parameters
    // G4String particleFilename = "particles.sh.bz2"; // Default input filename for particle data
    if (argc > 1) { // If a filename is provided as a command-line argument
        inputFilename = argv[1]; // Use the provided filename for simulation parameters
    }
    //if (argc > 2) { // If a second filename is provided as a command-line argument
      //  particleFilename = argv[2]; // Use the provided filename for particle data
    //}

    // Read dimensions and particle position from the input file
    G4ThreeVector worldSize; // Vector to store world dimensions
    G4ThreeVector particlePosition; // Vector to store particle position
    G4String unit = "m"; // Default unit
    G4String particleFilename; // Variable to store particle filename
    
    
    if (!ReadInputFile(inputFilename, worldSize, particlePosition, unit, particleFilename)) { // Read input file
        G4cerr << "Using default dimensions: 100km x 100km x 150km and particle position: (0, 0, 0)" << G4endl;
        worldSize = G4ThreeVector(100*km, 100*km, 150*km); // Default world dimensions
        particlePosition = G4ThreeVector(0, 0, 0); // Default particle position
        particleFilename = "particles.shw.bz2"; // Default particle filename
    }

    // Construct the default run manager
    G4RunManager* runManager = new G4RunManager; // Create a new run manager

    // Set mandatory initialization classes in the correct order
    runManager->SetUserInitialization(new DetectorConstruction(worldSize)); // Set detector construction
    runManager->SetUserInitialization(new PhysicsList()); // Set physics list
    ActionInitialization* actionInitialization = new ActionInitialization(); // Create action initialization
    runManager->SetUserInitialization(actionInitialization); // Set action initialization

    // Read particle data from the file
    ReadParticleFile(particleFilename, actionInitialization); // Read particle data and add to action initialization

    // Initialize G4 kernel
    runManager->Initialize(); // Initialize the run manager

    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive(); // Create a visualization manager
    visManager->Initialize(); // Initialize the visualization manager

    // Start interactive session
    G4UIExecutive* ui = new G4UIExecutive(argc, argv); // Create a UI executive

    // Get the pointer to the UI manager and set verbosities
    G4UImanager* UImanager = G4UImanager::GetUIpointer(); // Get the UI manager pointer
    UImanager->ApplyCommand("/run/verbose 1"); // Set run verbosity
    UImanager->ApplyCommand("/event/verbose 1"); // Set event verbosity
    UImanager->ApplyCommand("/tracking/verbose 1"); // Set tracking verbosity

    // Execute the initialization macro file
    UImanager->ApplyCommand("/control/execute init_vis.mac"); // Execute the visualization macro

    ui->SessionStart(); // Start the UI session
    delete ui; // Delete the UI executive

    // Job termination
    delete visManager; // Delete the visualization manager
    delete runManager; // Delete the run manager
    return 0; // Return 0 to indicate successful execution
}
