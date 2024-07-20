#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *); // Debe ser público
    G4int GetParticleCount() const; // Método para obtener el conteo de partículas

private:
    G4int particleCount; // Variable para contar las partículas
};

#endif

