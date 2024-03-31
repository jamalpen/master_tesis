// DetectorConstruction.cc
#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
   // Define materials
   G4NistManager* nist = G4NistManager::Instance();
   G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

   // Define solid volumes
   G4double world_sizeXY = 1*m;
   G4double world_sizeZ = 1*m;
   G4Box* solidWorld = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);

   // Define logical volumes
   G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, env_mat, "World");

   // Place physical volumes
   G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                     //no rotation
                                                     G4ThreeVector(),       //at (0,0,0)
                                                     logicWorld,            //its logical volume
                                                     "World",               //its name
                                                     0,                     //its mother  volume
                                                     false,                 //no boolean operation
                                                     0,                     //copy number
                                                     true);                 //overlaps checking

   return physWorld;
}
