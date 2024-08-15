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
}

PrimarySpectrumMessenger::~PrimarySpectrumMessenger()
{
  delete inFile;
  delete fSpecDir;
}

void PrimarySpectrumMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == inFile)
  {
    fSpectrum->inputFile = newValue;
    fSpectrum->openFile(newValue);
    //G4cout << "El nombre del archivo es: " << fSpectrum->inputFile << G4endl;
  }
}