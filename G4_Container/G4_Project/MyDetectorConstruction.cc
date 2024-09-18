#include "MyDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "GeometryMessenger.hh"
#include <cmath>

MyDetectorConstruction::MyDetectorConstruction(): worldSizeX(100*km), worldSizeY(100*km), worldSizeZ(100*km),
      detectorSizeX(10*km), detectorSizeY(10*km), detectorSizeZ(10*km), detectorPosX(0), detectorPosY(0), detectorPosZ(0),
      cylinderRadius(5*km), cylinderHeight(10*km), cylinderPosX(0), cylinderPosY(0), cylinderPosZ(30*km), magneticField(nullptr),
      fieldManager(nullptr), sensDet(nullptr)
{

    fGMessenger = new GeometryMessenger(this);

}

MyDetectorConstruction::~MyDetectorConstruction()
{

    delete fGMessenger;

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();

    // Definir el material del mundo como aire
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // Definir las dimensiones del mundo
    //G4double worldSizeX = 100 * km;
    //G4double worldSizeY = 100 * km;
    //G4double worldSizeZ = 100 * km;

    // Crear el volumen sólido del mundo como un paralelepípedo
    G4Box *solidWorld = new G4Box("solidWorld", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);

    // Crear el volumen lógico del mundo utilizando el material de aire
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // Colocar el volumen lógico del mundo en el volumen físico del mundo
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

    // Definir el material del detector fantasma como aire
    G4Material *ghostDetectorMat = nist->FindOrBuildMaterial("G4_AIR");

    // Definir las dimensiones del detector fantasma
    //G4double ghostSizeX = 1 * km;
    //G4double ghostSizeY = 1 * m;
    //G4double ghostSizeZ = 1 * km;
    //G4double ghostSizeZ = worldSizeZ;

    // Crear el volumen sólido del detector fantasma como un paralelepípedo
    G4Box *solidDetector = new G4Box("solidDetector", detectorSizeX / 2, detectorSizeY / 2, detectorSizeZ / 2);

    // Crear el volumen lógico del detector fantasma utilizando el material de aire
    logicDetector = new G4LogicalVolume(solidDetector, ghostDetectorMat, "logicDetector");

    // Colocar el volumen lógico del detector fantasma en el volumen lógico del mundo
    G4VPhysicalVolume *physGhostDetector = new G4PVPlacement(0, G4ThreeVector(detectorPosX, detectorPosY, detectorPosZ), logicDetector, "physDetector", logicWorld, false, 0, true);
    
    // Ahora creamos el cilindro
    G4Material* cylinderMat = nist->FindOrBuildMaterial("G4_AIR");

    // Crear el volumen sólido del cilindro
    G4Tubs* solidCylinder = new G4Tubs("solidCylinder", 0., cylinderRadius, cylinderHeight / 2, 0., 360*deg);

    // Crear el volumen lógico del cilindro utilizando el material de aire
    G4LogicalVolume* logicCylinder = new G4LogicalVolume(solidCylinder, cylinderMat, "logicCylinder");

    // Colocar el volumen lógico del cilindro en el volumen lógico del mundo
    G4VPhysicalVolume* physCylinder = new G4PVPlacement(0, G4ThreeVector(cylinderPosX, cylinderPosY, cylinderPosZ), logicCylinder, "physCylinder", logicWorld, false, 0, true);

    // Definir límites de producción
    //G4double maxStep = 10.0 * cm;
    //logicGhostDetector->SetUserLimits(new G4UserLimits(maxStep));

    //G4cout << "El tamaño inicial del mundo en x es: " << worldSizeX << G4endl;
    //G4cout << "El tamaño inicial del mundo en y es: " << worldSizeY << G4endl;
    //G4cout << "El tamaño inicial del mundo en z es: " << worldSizeZ << G4endl;
    //G4cout << "El tamano inicial del detector en x es: " << detectorSizeX << G4endl;
    //G4cout << "El tamano inicial del detector en y es: " << detectorSizeY << G4endl;
    //G4cout << "El tamano inicial del detector en z es: " << detectorSizeZ << G4endl;
    //G4cout << "La posición inicial del detector en x es: " << detectorPosX << G4endl;
    //G4cout << "La posición inicial del detector en y es: " << detectorPosY << G4endl;
    //G4cout << "La posición inicial del detector en z es: " << detectorPosZ << G4endl;

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();

    // Crear el detector sensible
    //MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");
    sensDet = new MySensitiveDetector("SensitiveDetector");

    // Registrar el detector sensible en el SDManager
    sdManager->AddNewDetector(sensDet);

    // Asignar el detector sensible al volumen lógico
    logicDetector->SetSensitiveDetector(sensDet);

    // Aquí se agrega el campo magnético
    G4ThreeVector fieldValue(26612.7e-9 * tesla, -2160.6e-9 * tesla, 9631.2e-9 * tesla);  
    magneticField = new G4UniformMagField(fieldValue);  // Crea el campo magnético

    fieldManager = new G4FieldManager(magneticField);  // Crea el Field Manager
    logicWorld->SetFieldManager(fieldManager, true);   // Asigna el campo al mundo madre

    G4cout << "Campo magnético configurado con componentes: "
           << "X = " << fieldValue.x()/tesla << " T, "
           << "Y = " << fieldValue.y()/tesla << " T, "
           << "Z = " << fieldValue.z()/tesla << " T." << G4endl;
    
    //Aquí es el mejor lugar para poder saber si las dimensiones del detector efectivamente cambian con geometry.mac o input.in
    G4cout << "Tamaño del mundo en X: " << worldSizeX << G4endl;
    G4cout << "Tamaño del mundo en Y: " << worldSizeY << G4endl;
    G4cout << "Tamaño del mundo en Z: " << worldSizeZ << G4endl;

    G4cout << "Tamaño del detector en X: " << detectorSizeX << G4endl;
    G4cout << "Tamaño del detector en Y: " << detectorSizeY << G4endl;
    G4cout << "Tamaño del detector en Z: " << detectorSizeZ << G4endl;

    G4cout << "Ubicación del detector en X: " << detectorPosX << G4endl;
    G4cout << "Ubicación del detector en Y: " << detectorPosY << G4endl;
    G4cout << "Ubicación del detector en Z: " << detectorPosZ << G4endl;

    // Aquí se puede verificar que las dimensiones del cilindro se hayan aplicado correctamente
    G4cout << "Tamaño del cilindro: radio = " << cylinderRadius << " y altura = " << cylinderHeight << G4endl;
    G4cout << "Ubicación del cilindro: X = " << cylinderPosX << ", Y = " << cylinderPosY << ", Z = " << cylinderPosZ << G4endl;  
}

MySensitiveDetector* MyDetectorConstruction::GetSensitiveDetector() const {
    return sensDet;
}

void MyDetectorConstruction::SetWorldSizeX(G4double newWorldSizeX) {
    worldSizeX = newWorldSizeX;
    //G4cout << "El tamaño del mundo en X es: " << worldSizeX << G4endl;
}

void MyDetectorConstruction::SetWorldSizeY(G4double newWorldSizeY) {
    worldSizeY = newWorldSizeY;
    //G4cout << "El tamaño del mundo en Y es: " << worldSizeY << G4endl;
}

void MyDetectorConstruction::SetWorldSizeZ(G4double newWorldSizeZ) {
    worldSizeZ = newWorldSizeZ;
    //G4cout << "El tamaño del mundo en Z es: " << worldSizeZ << G4endl;
}

void MyDetectorConstruction::SetDetectorSizeX(G4double newDetectorSizeX) {
    detectorSizeX = newDetectorSizeX;
    //G4cout << "El tamaño del detector en X es: " << detectorSizeX << G4endl;
}

void MyDetectorConstruction::SetDetectorSizeY(G4double newDetectorSizeY) {
    detectorSizeY = newDetectorSizeY;
    //G4cout << "El tamaño del detector en Y es: " << detectorSizeY << G4endl;
}

void MyDetectorConstruction::SetDetectorSizeZ(G4double newDetectorSizeZ) {
    detectorSizeZ = newDetectorSizeZ;
    //G4cout << "El tamaño del detector en Z es: " << detectorSizeZ << G4endl;
}

void MyDetectorConstruction::SetDetectorPosX(G4double newPosX)
{
    detectorPosX = newPosX;
    //G4cout << "El posición en el eje x del detector es: " << detectorPosX << G4endl;
}

void MyDetectorConstruction::SetDetectorPosY(G4double newPosY)
{
    detectorPosY = newPosY;
    //G4cout << "El posición en el eje y del detector es: " << detectorPosY << G4endl;
}

void MyDetectorConstruction::SetDetectorPosZ(G4double newPosZ)
{
    detectorPosZ = newPosZ;
    //G4cout << "El posición en el eje z del detector es: " << detectorPosZ << G4endl;
}

void MyDetectorConstruction::SetCylinderRadius(G4double radius) {
    cylinderRadius = radius;
}

void MyDetectorConstruction::SetCylinderHeight(G4double height) {
    cylinderHeight = height;
}

void MyDetectorConstruction::SetCylinderPosX(G4double posX) {
    cylinderPosX = posX;
}

void MyDetectorConstruction::SetCylinderPosY(G4double posY) {
    cylinderPosY = posY;
}

void MyDetectorConstruction::SetCylinderPosZ(G4double posZ) {
    cylinderPosZ = posZ;
}

