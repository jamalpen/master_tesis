#include "PrimarySpectrumMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"
// C++ Libraries
#include <string>  
#include <fstream>
#include <sstream>

PrimarySpectrumMessenger::PrimarySpectrumMessenger(PrimarySpectrum* spectrum)
  : G4UImessenger(),
    fSpectrum(spectrum)
{
  G4cout << "...PrimarySpectrumMessenger..." << G4endl;
  fSpecDir = new G4UIdirectory("/spectrum/");
  fSpecDir->SetGuidance("PrimarySpectrum control");

  inFile = new G4UIcmdWithAString("/spectrum/readfile", this); 
  inFile->SetGuidance("Set input file name");
  inFile->SetParameterName("InputFile", false);

  xInit = new G4UIcmdWithADoubleAndUnit("/spectrum/iniposX", this);
  xInit->SetGuidance("Set initial X position");
  xInit->SetParameterName("XInit", false);
  xInit->SetUnitCategory("Length");

  yInit = new G4UIcmdWithADoubleAndUnit("/spectrum/iniposY", this);
  yInit->SetGuidance("Set initial Y position");
  yInit->SetParameterName("YInit", false);
  yInit->SetUnitCategory("Length");

  zInit = new G4UIcmdWithADoubleAndUnit("/spectrum/iniposZ", this);
  zInit->SetGuidance("Set initial Z position");
  zInit->SetParameterName("ZInit", false);
  zInit->SetUnitCategory("Length");

  areaDimX = new G4UIcmdWithADoubleAndUnit("/spectrum/areaDimX", this);
  areaDimX->SetGuidance("Set X dimension of the area");
  areaDimX->SetParameterName("AreaDimX", false);
  areaDimX->SetUnitCategory("Length");

  areaDimY = new G4UIcmdWithADoubleAndUnit("/spectrum/areaDimY", this);
  areaDimY->SetGuidance("Set Y dimension of the area");
  areaDimY->SetParameterName("AreaDimY", false);
  areaDimY->SetUnitCategory("Length");

  areaDimZ = new G4UIcmdWithADoubleAndUnit("/spectrum/areaDimZ", this);
  areaDimZ->SetGuidance("Set Z dimension of the area");
  areaDimZ->SetParameterName("AreaDimZ", false);
  areaDimZ->SetUnitCategory("Length");
}

PrimarySpectrumMessenger::~PrimarySpectrumMessenger()
{
  delete inFile;
  delete xInit;
  delete yInit;
  delete zInit;
  delete areaDimX;
  delete areaDimY;
  delete areaDimZ;
  delete fSpecDir;
}

void PrimarySpectrumMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == inFile)
  {
    fSpectrum->inputFile = newValue;
    fSpectrum->openFile(newValue);
  }

  if (command == xInit)
    fSpectrum->setInitPosX(xInit->GetNewDoubleValue(newValue));

  if (command == yInit)
    fSpectrum->setInitPosY(yInit->GetNewDoubleValue(newValue));

  if (command == zInit)
    fSpectrum->setInitPosZ(zInit->GetNewDoubleValue(newValue));

  if (command == areaDimX)
    fSpectrum->setAreaDimX(areaDimX->GetNewDoubleValue(newValue));

  if (command == areaDimY)
    fSpectrum->setAreaDimY(areaDimY->GetNewDoubleValue(newValue));

  if (command == areaDimZ)
    fSpectrum->setAreaDimZ(areaDimZ->GetNewDoubleValue(newValue));
}