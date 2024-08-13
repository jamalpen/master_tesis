#include "MyDetectorConstruction.hh"
#include "G4SDManager.hh"
#include <cmath>

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();

    // Definir el material del mundo como aire
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // Definir las dimensiones del mundo
    G4double worldSizeX = 100 * km;
    G4double worldSizeY = 100 * km;
    G4double worldSizeZ = 100 * km;

    // Crear el volumen sólido del mundo como un paralelepípedo
    G4Box *solidWorld = new G4Box("solidWorld", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);

    // Crear el volumen lógico del mundo utilizando el material de aire
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // Colocar el volumen lógico del mundo en el volumen físico del mundo
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Definir el material del detector fantasma como aire
    G4Material *ghostDetectorMat = nist->FindOrBuildMaterial("G4_AIR");

    // Definir las dimensiones del detector fantasma
    G4double ghostSizeX = 1 * km;
    G4double ghostSizeY = 1 * km;
    //G4double ghostSizeZ = 100 * km;
    G4double ghostSizeZ = worldSizeZ;

    // Crear el volumen sólido del detector fantasma como un paralelepípedo
    G4Box *solidGhostDetector = new G4Box("solidGhostDetector", ghostSizeX / 2, ghostSizeY / 2, ghostSizeZ / 2);

    // Crear el volumen lógico del detector fantasma utilizando el material de aire
    logicGhostDetector = new G4LogicalVolume(solidGhostDetector, ghostDetectorMat, "logicGhostDetector");

    // Colocar el volumen lógico del detector fantasma en el volumen lógico del mundo
    G4VPhysicalVolume *physGhostDetector = new G4PVPlacement(0, G4ThreeVector(0., 50, 0.), logicGhostDetector, "physGhostDetector", logicWorld, false, 0, true);
    
    // Definir límites de producción
    //G4double maxStep = 10.0 * cm;
    //logicGhostDetector->SetUserLimits(new G4UserLimits(maxStep));

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();

    // Crear el detector sensible
    MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");

    // Registrar el detector sensible en el SDManager
    sdManager->AddNewDetector(sensDet);

    // Asignar el detector sensible al volumen lógico
    logicGhostDetector->SetSensitiveDetector(sensDet);
}

