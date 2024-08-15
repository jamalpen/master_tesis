#include "GeometryMessenger.hh"
#include "MyDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"

// C++ Libraries
#include <string>
#include <fstream>
#include <sstream>

GeometryMessenger::GeometryMessenger(MyDetectorConstruction* detectorConstruction)
  : G4UImessenger(),
    fDetectorConstruction(detectorConstruction)
{
  fGeometryDir = new G4UIdirectory("/geometry/");
  fGeometryDir->SetGuidance("Geometry control");

  worldSizeXCmd = new G4UIcmdWithADoubleAndUnit("/geometry/worldSizeX", this);
  worldSizeXCmd->SetGuidance("Set X dimension of the world");
  worldSizeXCmd->SetParameterName("WorldSizeX", true);
  worldSizeXCmd->SetUnitCategory("Length");
  
  worldSizeYCmd = new G4UIcmdWithADoubleAndUnit("/geometry/worldSizeY", this);
  worldSizeYCmd->SetGuidance("Set Y dimension of the world");
  worldSizeYCmd->SetParameterName("WorldSizeY", true);
  worldSizeYCmd->SetUnitCategory("Length");
  
  worldSizeZCmd = new G4UIcmdWithADoubleAndUnit("/geometry/worldSizeZ", this);
  worldSizeZCmd->SetGuidance("Set Z dimension of the world");
  worldSizeZCmd->SetParameterName("WorldSizeZ", true);
  worldSizeZCmd->SetUnitCategory("Length");

  detectorSizeXCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detectorSizeX", this);
  detectorSizeXCmd->SetGuidance("Set X dimension of the detector");
  detectorSizeXCmd->SetParameterName("DetectorSizeX", true);
  detectorSizeXCmd->SetUnitCategory("Length");

  detectorSizeYCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detectorSizeY", this);
  detectorSizeYCmd->SetGuidance("Set Y dimension of the detector");
  detectorSizeYCmd->SetParameterName("DetectorSizeY", true);
  detectorSizeYCmd->SetUnitCategory("Length");

  detectorSizeZCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detectorSizeZ", this);
  detectorSizeZCmd->SetGuidance("Set Z dimension of the detector");
  detectorSizeZCmd->SetParameterName("DetectorSizeZ", true);
  detectorSizeZCmd->SetUnitCategory("Length");
}

GeometryMessenger::~GeometryMessenger()
{
  delete worldSizeXCmd;
  delete worldSizeYCmd;
  delete worldSizeZCmd;
  delete detectorSizeXCmd;
  delete detectorSizeYCmd;
  delete detectorSizeZCmd;
  delete fGeometryDir;
}

void GeometryMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == worldSizeXCmd) {
    fDetectorConstruction->SetWorldSizeX(worldSizeXCmd->GetNewDoubleValue(newValue));
  }

  if (command == worldSizeYCmd) {
    fDetectorConstruction->SetWorldSizeY(worldSizeYCmd->GetNewDoubleValue(newValue));
  }

  if (command == worldSizeZCmd) {
    fDetectorConstruction->SetWorldSizeZ(worldSizeZCmd->GetNewDoubleValue(newValue));
  }

  if (command == detectorSizeXCmd) {
    fDetectorConstruction->SetDetectorSizeX(detectorSizeXCmd->GetNewDoubleValue(newValue));
  }

  if (command == detectorSizeYCmd) {
    fDetectorConstruction->SetDetectorSizeY(detectorSizeYCmd->GetNewDoubleValue(newValue));
  }

  if (command == detectorSizeZCmd) {
    fDetectorConstruction->SetDetectorSizeZ(detectorSizeZCmd->GetNewDoubleValue(newValue));
  }
}
