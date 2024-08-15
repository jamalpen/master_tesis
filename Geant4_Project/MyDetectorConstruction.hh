#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "MySensitiveDetector.hh"

class GeometryMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

//    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();

    //Métodos para actualizar las dimensiones del mundo y el detector
    void SetWorldSizeX(G4double worldSizeX);
    void SetWorldSizeY(G4double worldSizeY);
    void SetWorldSizeZ(G4double worldSizeZ);
    void SetDetectorSizeX(G4double detectorSizeX);
    void SetDetectorSizeY(G4double detectorSizeY);
    void SetDetectorSizeZ(G4double detectorSizeZ);

private:

    G4double worldSizeX, worldSizeY, worldSizeZ;
    G4double detectorSizeX, detectorSizeY, detectorSizeZ;

    G4LogicalVolume *logicDetector;

    GeometryMessenger* fGMessenger; // Puntero a GeometryMessenger

    virtual void ConstructSDandField();
};

#endif
