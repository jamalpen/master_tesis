#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    void SetWorldDimensions(G4ThreeVector dims);

private:
    G4ThreeVector worldDimensions;

    class Messenger : public G4UImessenger {
    public:
        Messenger(MyDetectorConstruction* det);
        ~Messenger();
        void SetNewValue(G4UIcommand* command, G4String newValue);
    private:
        MyDetectorConstruction* fDetector;
        G4UIcmdWith3VectorAndUnit* fWorldDimensionsCmd;
    };
    Messenger* fMessenger;
};

#endif

