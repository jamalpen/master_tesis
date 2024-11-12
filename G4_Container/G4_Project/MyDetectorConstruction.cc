#include "MyDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "GeometryMessenger.hh"
#include <cmath>
#include "G4NistManager.hh"
#include "G4SimpleRunge.hh"

MyDetectorConstruction::MyDetectorConstruction(): worldSizeX(100*km), worldSizeY(100*km), worldSizeZ(100*km),
      detectorSizeX(10*km), detectorSizeY(10*km), detectorSizeZ(10*km), detectorPosX(0), detectorPosY(0), detectorPosZ(0),
      cylinderRadius(5*km), cylinderHeight(10*km), cylinderPosX(0), cylinderPosY(0), cylinderPosZ(30*km), magneticField(nullptr),
      worldfieldManager(nullptr), sensDet(nullptr)
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
    logicCylinder = new G4LogicalVolume(solidCylinder, cylinderMat, "logicCylinder");

    // Colocar el volumen lógico del cilindro en el volumen lógico del mundo
    G4VPhysicalVolume* physCylinder = new G4PVPlacement(0, G4ThreeVector(cylinderPosX, cylinderPosY, cylinderPosZ), logicCylinder, "physCylinder", logicWorld, false, 0, true);
    
    if (logicCylinder) {
    G4cout << "logicCylinder successfully initialized in Construct()." << G4endl;
    } else {
    G4cerr << "Error: logicCylinder failed to initialize in Construct()." << G4endl;
    }

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

    // Ensure the logical volume for the cylinder exists
    if (!logicCylinder) {
        G4cerr << "Error: logicCylinder not initialized!" << G4endl;
        return;
    }

    // Create the sensitive detector
    sensDet = new MySensitiveDetector("SensitiveDetector");

    // Register the sensitive detector with the SDManager
    sdManager->AddNewDetector(sensDet);

    // Assign the sensitive detector to the logical volume
    logicDetector->SetSensitiveDetector(sensDet);

    // Here, the magnetic field is added to the mother world
    magneticFieldValue = G4ThreeVector(26612.7e-9 * tesla, -2160.6e-9 * tesla, 9631.2e-9 * tesla);  
    magneticField = new G4UniformMagField(magneticFieldValue);  // Create the magnetic field

    worldfieldManager = new G4FieldManager(magneticField);  // Create the Field Manager
    logicWorld->SetFieldManager(worldfieldManager, true);   // Assign the field to the mother world

    G4cout << "Magnetic field configured in mother world with components: "
           << "X = " << magneticFieldValue.x()/tesla << " T, "
           << "Y = " << magneticFieldValue.y()/tesla << " T, "
           << "Z = " << magneticFieldValue.z()/tesla << " T." << G4endl;

    // Configure the electric field in the cylinder
    electricFieldVector = G4ThreeVector(0.,0.,-1000000.0 * volt/m); // Electric field
    //electricFieldVector = G4ThreeVector(0.,0.,  100.0 * volt/m); // Example of Electric field
    // Instance of CylindricalEMFieldSetup to apply the field to the cylinder
    cylEMFieldSetup = new CylindricalElectricFieldSetup(logicCylinder, electricFieldVector);

    G4cout << "Electric field configured in the cylinder." << G4endl;
    G4cout << "Electric field in the cylinder configured with components: "
           << "X = " << electricFieldVector.x()/(volt/m) << " V/m, "
           << "Y = " << electricFieldVector.y()/(volt/m) << " V/m, "
           << "Z = " << electricFieldVector.z()/(volt/m) << " V/m." << G4endl;

    
    
    // Define the magnetic field vector in Tesla
    magneticFieldVector = G4ThreeVector(0., 0., 0.); // Magnetic field
    /*//magneticFieldVector = G4ThreeVector(1.0 * tesla, 0., 0.); // Magnetic field
    // Create an instance of CylindricalMagneticFieldSetup to apply the magnetic field only to the cylinder
    fMagneticFieldSetup = new CylindricalMagneticFieldSetup(logicCylinder, magneticFieldVector);

    G4cout << "Magnetic field configured in the cylinder." << G4endl;
    G4cout << "Magnetic field in the cylinder set with components: "
           << "X = " << magneticFieldVector.x()/tesla << " T, "
           << "Y = " << magneticFieldVector.y()/tesla << " T, "
           << "Z = " << magneticFieldVector.z()/tesla << " T." << G4endl;*/


    // Here we can verify that the dimensions of the cylinder have been correctly applied
    G4cout << "World and detector sizes and positions:" << G4endl;
    G4cout << "World size: X = " << worldSizeX << G4endl;
    G4cout << "World size: Y = " << worldSizeY << G4endl;
    G4cout << "World size: Z = " << worldSizeZ << G4endl;

    G4cout << "Detector size: X = " << detectorSizeX << G4endl;
    G4cout << "Detector size: Y = " << detectorSizeY << G4endl;
    G4cout << "Detector size: Z = " << detectorSizeZ << G4endl;

    G4cout << "Detector position: X = " << detectorPosX << G4endl;
    G4cout << "Detector position: Y = " << detectorPosY << G4endl;
    G4cout << "Detector position: Z = " << detectorPosZ << G4endl;

    G4cout << "Cylinder size: Radius = " << cylinderRadius << " and Height =  " << cylinderHeight << G4endl;
    G4cout << "Cylinder position: X = " << cylinderPosX << ", Y = " << cylinderPosY << ", Z = " << cylinderPosZ << G4endl;  
}

MySensitiveDetector* MyDetectorConstruction::GetSensitiveDetector() const {
    return sensDet;
}

G4ThreeVector MyDetectorConstruction::GetMagneticFieldValue() const {
    return magneticFieldValue;
}

G4ThreeVector MyDetectorConstruction::GetCylinderMagneticField() const {
    return magneticFieldVector;
}

G4ThreeVector MyDetectorConstruction::GetCylinderElectricField() const {
    return electricFieldVector;
}

G4double MyDetectorConstruction::GetWorldSizeX() const {
    return worldSizeX;
}

G4double MyDetectorConstruction::GetWorldSizeY() const {
    return worldSizeY;
}

G4double MyDetectorConstruction::GetWorldSizeZ() const {
    return worldSizeZ;
}

G4double MyDetectorConstruction::GetDetectorSizeX() const {
    return detectorSizeX;
}

G4double MyDetectorConstruction::GetDetectorSizeY() const {
    return detectorSizeY;
}

G4double MyDetectorConstruction::GetDetectorSizeZ() const {
    return detectorSizeZ;
}

G4double MyDetectorConstruction::GetDetectorPosX() const {
    return detectorPosX;
}

G4double MyDetectorConstruction::GetDetectorPosY() const {
    return detectorPosY;
}

G4double MyDetectorConstruction::GetDetectorPosZ() const {
    return detectorPosZ;
}

G4double MyDetectorConstruction::GetCylinderRadius() const {
    return cylinderRadius;
}

G4double MyDetectorConstruction::GetCylinderHeight() const {
    return cylinderHeight;
}

G4double MyDetectorConstruction::GetCylinderPosX() const {
    return cylinderPosX;
}

G4double MyDetectorConstruction::GetCylinderPosY() const {
    return cylinderPosY;
}

G4double MyDetectorConstruction::GetCylinderPosZ() const {
    return cylinderPosZ;
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
