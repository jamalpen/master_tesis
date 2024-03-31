// RunAction.cc
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
: G4UserRunAction()
{ }

RunAction::~RunAction()
{ }

void RunAction::BeginOfRunAction(const G4Run*)
{
   // Código para ejecutar al inicio de cada run, por ejemplo, abrir archivos de datos
}

void RunAction::EndOfRunAction(const G4Run*)
{
   // Código para ejecutar al final de cada run, por ejemplo, cerrar archivos de datos
}
