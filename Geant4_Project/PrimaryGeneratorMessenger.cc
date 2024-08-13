#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"

// C++ Libraries
//
#include <string>
#include <fstream>
#include <sstream>

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
  : G4UImessenger(),
    fAction(Gun)
{
  G4cout << "...PrimaryGeneratorMessenger..." << G4endl;
  fGunDir = new G4UIdirectory("/gun/");
  fGunDir->SetGuidance("PrimaryGenerator control");

  fPolarCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/optPhotonPolar", this);
  fPolarCmd->SetGuidance("Set linear polarization");
  fPolarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  fPolarCmd->SetParameterName("angle", true);
  fPolarCmd->SetUnitCategory("Angle");
  fPolarCmd->SetDefaultValue(-360.0);
  fPolarCmd->SetDefaultUnit("deg");
  fPolarCmd->AvailableForStates(G4State_Idle);

  valueForTest = new G4UIcmdWithADoubleAndUnit("/spectrum/testVal", this);
  valueForTest->SetGuidance("Just for learning how this class works");
  valueForTest->SetDefaultUnit("MeV");

  xInitCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/iniposX", this);
  xInitCmd->SetGuidance("Set initial X position");
  xInitCmd->SetParameterName("XInit", true);
  xInitCmd->SetUnitCategory("Length");
  xInitCmd->SetDefaultValue(0.0);
  xInitCmd->SetDefaultUnit("mm");

  yInitCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/iniposY", this);
  yInitCmd->SetGuidance("Set initial Y position");
  yInitCmd->SetParameterName("YInit", true);
  yInitCmd->SetUnitCategory("Length");
  yInitCmd->SetDefaultValue(0.0);
  yInitCmd->SetDefaultUnit("mm");

  zInitCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/iniposZ", this);
  zInitCmd->SetGuidance("Set initial Z position");
  zInitCmd->SetParameterName("ZInit", true);
  zInitCmd->SetUnitCategory("Length");
  zInitCmd->SetDefaultValue(0.0);
  zInitCmd->SetDefaultUnit("mm");

  areaDimXCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/areaDimX", this);
  areaDimXCmd->SetGuidance("Set X dimension of the area");
  areaDimXCmd->SetParameterName("AreaDimX", true);
  areaDimXCmd->SetUnitCategory("Length");
  areaDimXCmd->SetDefaultValue(1.0);
  areaDimXCmd->SetDefaultUnit("mm");

  areaDimYCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/areaDimY", this);
  areaDimYCmd->SetGuidance("Set Y dimension of the area");
  areaDimYCmd->SetParameterName("AreaDimY", true);
  areaDimYCmd->SetUnitCategory("Length");
  areaDimYCmd->SetDefaultValue(1.0);
  areaDimYCmd->SetDefaultUnit("mm");

  areaDimZCmd = new G4UIcmdWithADoubleAndUnit("/spectrum/areaDimZ", this);
  areaDimZCmd->SetGuidance("Set Z dimension of the area");
  areaDimZCmd->SetParameterName("AreaDimZ", true);
  areaDimZCmd->SetUnitCategory("Length");
  areaDimZCmd->SetDefaultValue(1.0);
  areaDimZCmd->SetDefaultUnit("mm");
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fPolarCmd;
  delete fGunDir;
  delete valueForTest;
  delete xInitCmd;
  delete yInitCmd;
  delete zInitCmd;
  delete areaDimXCmd;
  delete areaDimYCmd;
  delete areaDimZCmd;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fPolarCmd) {
    G4double angle = fPolarCmd->GetNewDoubleValue(newValue);
    if (angle == -360.0 * deg) {
      fAction->SetOptPhotonPolar();
    } else {
      fAction->SetOptPhotonPolar(angle);
    }
  }

  if (command == valueForTest) {
    G4cout << "Testing Messenger Class" << G4endl;
    G4cout << valueForTest->GetNewDoubleValue(newValue) << G4endl;
  }

  if (command == xInitCmd) {
    fAction->fCrkPar->setInitPosX(xInitCmd->GetNewDoubleValue(newValue));
  }

  if (command == yInitCmd) {
    fAction->fCrkPar->setInitPosY(yInitCmd->GetNewDoubleValue(newValue));
  }

  if (command == zInitCmd) {
    fAction->fCrkPar->setInitPosZ(zInitCmd->GetNewDoubleValue(newValue));
  }

  if (command == areaDimXCmd) {
    fAction->fCrkPar->setAreaDimX(areaDimXCmd->GetNewDoubleValue(newValue));
  }

  if (command == areaDimYCmd) {
    fAction->fCrkPar->setAreaDimY(areaDimYCmd->GetNewDoubleValue(newValue));
  }

  if (command == areaDimZCmd) {
    fAction->fCrkPar->setAreaDimZ(areaDimZCmd->GetNewDoubleValue(newValue));
  }
}

void PrimaryGeneratorMessenger::SetParticleMomentum(G4ThreeVector direction)
{
  double px = direction.x();
  double py = direction.y();
  double pz = direction.z();

  std::string sPx = std::to_string(px);
  std::string sPy = std::to_string(py);
  std::string sPz = std::to_string(pz);
  std::string momentum = "momentum " + sPx + " " + sPy + " " + sPz + " GeV";

  G4UIcmdWithADoubleAndUnit* testCmd = new G4UIcmdWithADoubleAndUnit("gun/energy 100 MeV", this);

  testCmd->SetGuidance(momentum.c_str());
//  testCmd->SetGuidance("100 MeV");
}

