// EventAction.cc
#include "EventAction.hh"
#include "G4Event.hh"

EventAction::EventAction()
: G4UserEventAction()
{ }

EventAction::~EventAction()
{ }

void EventAction::BeginOfEventAction(const G4Event*)
{
   // Código para ejecutar al inicio de cada evento, por ejemplo, inicializar contadores
}

void EventAction::EndOfEventAction(const G4Event*)
{
   // Código para ejecutar al final de cada evento, por ejemplo, escribir resultados a archivo
}

