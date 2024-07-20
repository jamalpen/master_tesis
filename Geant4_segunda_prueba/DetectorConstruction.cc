#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"

DetectorConstruction::DetectorConstruction(G4ThreeVector worldSize)
: G4VUserDetectorConstruction(),
  fWorldSize(worldSize),
  logicWorld(nullptr)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
   // Define materials
   G4NistManager* nist = G4NistManager::Instance();
   G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

   // Define solid volumes
   G4Box* solidWorld = new G4Box("World", fWorldSize.x() / 2, fWorldSize.y() / 2, fWorldSize.z() / 2);

   // Define logical volumes
   logicWorld = new G4LogicalVolume(solidWorld, env_mat, "World");
   
   // Set user limits for step length
   G4double maxStep = 1.0 * m;
   G4UserLimits* userLimits = new G4UserLimits(maxStep);
   logicWorld->SetUserLimits(userLimits);

   // Place physical volumes
   G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                     // no rotation
                                                     G4ThreeVector(0,0,0), // at origin
                                                     logicWorld,            // its logical volume
                                                     "World",               // its name
                                                     0,                     // its mother volume
                                                     false,                 // no boolean operation
                                                     0,                     // copy number
                                                     true);                 // overlaps checking

   return physWorld;
}
