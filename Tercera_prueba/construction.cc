#include "construction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include <iostream>

MyDetectorConstruction::MyDetectorConstruction()
    : worldDimensions(G4ThreeVector(0.5 * m, 0.5 * m, 0.5 * m))
{
    fMessenger = new Messenger(this);
}

MyDetectorConstruction::~MyDetectorConstruction() {
    delete fMessenger;
}

void MyDetectorConstruction::SetWorldDimensions(G4ThreeVector dims) {
    worldDimensions = dims;
}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box *solidWorld = new G4Box("solidWorld", worldDimensions.x(), worldDimensions.y(), worldDimensions.z());
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    return physWorld;
}

// Implementación de la clase Messenger
MyDetectorConstruction::Messenger::Messenger(MyDetectorConstruction* det)
    : G4UImessenger(), fDetector(det)
{
    fWorldDimensionsCmd = new G4UIcmdWith3VectorAndUnit("/mydetector/worldDimensions", this);
    fWorldDimensionsCmd->SetGuidance("Set world dimensions.");
    fWorldDimensionsCmd->SetParameterName("X", "Y", "Z", true);
    fWorldDimensionsCmd->SetDefaultUnit("km");
    fWorldDimensionsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

MyDetectorConstruction::Messenger::~Messenger() {
    delete fWorldDimensionsCmd;
}

void MyDetectorConstruction::Messenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if (command == fWorldDimensionsCmd) {
        fDetector->SetWorldDimensions(fWorldDimensionsCmd->GetNew3VectorValue(newValue));
    }
}
