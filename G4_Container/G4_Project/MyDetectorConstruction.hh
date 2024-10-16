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
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"

#include "MySensitiveDetector.hh"

class GeometryMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

//    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();

    // Methods to update world and detector dimensions and detector position
    void SetWorldSizeX(G4double worldSizeX);
    void SetWorldSizeY(G4double worldSizeY);
    void SetWorldSizeZ(G4double worldSizeZ);

    void SetCylinderRadius(G4double cylinderRadius);    // For cylindrical world
    void SetCylinderHeight(G4double cylinderHeight);    // For cylindrical world

    void SetCylinderPosX(G4double cylinderPosX);  // Nueva posición del cilindro
    void SetCylinderPosY(G4double cylinderPosY);
    void SetCylinderPosZ(G4double cylinderPosZ);

    void SetDetectorSizeX(G4double detectorSizeX);
    void SetDetectorSizeY(G4double detectorSizeY);
    void SetDetectorSizeZ(G4double detectorSizeZ);

    void SetDetectorPosX(G4double detectorPosX);
    void SetDetectorPosY(G4double detectorPosY);
    void SetDetectorPosZ(G4double detectorPosZ);

    // Método para obtener el detector sensible
    MySensitiveDetector* GetSensitiveDetector() const;

    // Métodos para obtener los valores del campo magnético
    G4ThreeVector GetMagneticFieldValue() const;

private:

    // Dimensions for cubic world
    G4double worldSizeX, worldSizeY, worldSizeZ;

    // Dimensions and position of the detector
    G4double detectorSizeX, detectorSizeY, detectorSizeZ;
    G4double detectorPosX, detectorPosY, detectorPosZ;

    // Dimensions and position for cylindrical world
    G4double cylinderRadius, cylinderHeight;
    G4double cylinderPosX, cylinderPosY, cylinderPosZ;

    G4LogicalVolume* logicWorld;
    G4LogicalVolume *logicDetector;
    GeometryMessenger* fGMessenger; // Pointer to GeometryMessenger, important
    MySensitiveDetector* sensDet; // Pointer to the sensitive detector

    // Para mi campo magnético
    G4UniformMagField* magneticField;  // Puntero al campo magnético uniforme
    G4FieldManager* fieldManager;      // Puntero al Field Manager
    G4ThreeVector magneticFieldValue;  // Store the field value manually

    virtual void ConstructSDandField();
};

#endif