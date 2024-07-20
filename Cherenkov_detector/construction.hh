#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
// Header guard to prevent multiple inclusions of this header file

class MyDetectorConstruction : public G4VUserDetectorConstruction {
    // Define the MyDetectorConstruction class inheriting from G4UserDetectorConstruction

public:
    MyDetectorConstruction();
    // Constructor declaration

    ~MyDetectorConstruction();
    // Destructor declaration
    
    virtual G4VPhysicalVolume *Construct();
    // Declaration of the Construct method, which overrides a virtual method
    // from G4UserDetectorConstruction and returns a pointer to G4VPhysicalVolume
};

#endif
// End of header guard

