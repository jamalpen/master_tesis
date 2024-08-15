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
  
  //Comandos para el mundo madre de Geant4
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
 
  //Comandos para el tamaño del detector dentro del mundo de Geant4
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

  //Comandos para la posición del detector dentro del mundo de Geant4
  detectorPosXCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detectorPosX", this);
  detectorPosXCmd->SetGuidance("Set X position of the detector");
  detectorPosXCmd->SetParameterName("DetectorPosX", true); 
  detectorPosXCmd->SetUnitCategory("Length");

  detectorPosYCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detectorPosY", this);
  detectorPosYCmd->SetGuidance("Set Y position of the detector");
  detectorPosYCmd->SetParameterName("DetectorPosY", false);
  detectorPosYCmd->SetUnitCategory("Length");

  detectorPosZCmd = new G4UIcmdWithADoubleAndUnit("/geometry/detectorPosZ", this);
  detectorPosZCmd->SetGuidance("Set Z position of the detector");
  detectorPosZCmd->SetParameterName("DetectorPosZ", false);
  detectorPosZCmd->SetUnitCategory("Length");

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
  delete detectorPosXCmd;
  delete detectorPosYCmd;
  delete detectorPosZCmd;
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

  if (command == detectorPosXCmd)
  {
    fDetectorConstruction->SetDetectorPosX(detectorPosXCmd->GetNewDoubleValue(newValue));
  }

  if (command == detectorPosYCmd)
  {
    fDetectorConstruction->SetDetectorPosY(detectorPosYCmd->GetNewDoubleValue(newValue));
  }
  
  if (command == detectorPosZCmd)
  {
    fDetectorConstruction->SetDetectorPosZ(detectorPosZCmd->GetNewDoubleValue(newValue));
  }
}
