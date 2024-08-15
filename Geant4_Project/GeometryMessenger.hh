#ifndef GEOMETRYMESSENGER_HH
#define GEOMETRYMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class MyDetectorConstruction; // Adelantamos la declaración para usar la clase
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class GeometryMessenger : public G4UImessenger
{
public:
    GeometryMessenger(MyDetectorConstruction* detectorConstruction);
    virtual ~GeometryMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    MyDetectorConstruction* fDetectorConstruction;

    G4UIdirectory* fGeometryDir;
    G4UIcmdWithADoubleAndUnit* worldSizeXCmd;
    G4UIcmdWithADoubleAndUnit* worldSizeYCmd;
    G4UIcmdWithADoubleAndUnit* worldSizeZCmd;
    G4UIcmdWithADoubleAndUnit* detectorSizeXCmd;
    G4UIcmdWithADoubleAndUnit* detectorSizeYCmd;
    G4UIcmdWithADoubleAndUnit* detectorSizeZCmd;
};

#endif
