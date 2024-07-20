#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
   DetectorConstruction(G4ThreeVector worldSize);
   virtual ~DetectorConstruction();

   virtual G4VPhysicalVolume* Construct();

private:
   G4ThreeVector fWorldSize; // World dimensions
   G4LogicalVolume* logicWorld; // Logical volume of the world
};

#endif

