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
    //delete cylinderMagneticField;
    //delete cylinderFieldManager;

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

    // Crear el detector sensible
    //MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");
    sensDet = new MySensitiveDetector("SensitiveDetector");

    // Registrar el detector sensible en el SDManager
    sdManager->AddNewDetector(sensDet);

    // Asignar el detector sensible al volumen lógico
    logicDetector->SetSensitiveDetector(sensDet);

    /*// Aquí se agrega el campo magnético al mundo madre
    magneticFieldValue = G4ThreeVector(26612.7e-9 * tesla, -2160.6e-9 * tesla, 9631.2e-9 * tesla);  
    magneticField = new G4UniformMagField(magneticFieldValue);  // Crea el campo magnético

    worldfieldManager = new G4FieldManager(magneticField);  // Crea el Field Manager
    logicWorld->SetFieldManager(worldfieldManager, true);   // Asigna el campo al mundo madre

    G4cout << "Campo magnético configurado con componentes: "
           << "X = " << magneticFieldValue.x()/tesla << " T, "
           << "Y = " << magneticFieldValue.y()/tesla << " T, "
           << "Z = " << magneticFieldValue.z()/tesla << " T." << G4endl;*/

       

    // Magnetic field for the cylindrical volume only
    G4ThreeVector cylinderMagneticFieldVector(100e-9 * tesla, 0., 0.);
    cylinderMagneticField = new G4UniformMagField(cylinderMagneticFieldVector);

    // Field manager for the cylinder
    cylinderFieldManager = new G4FieldManager(cylinderMagneticField);
    logicCylinder->SetFieldManager(cylinderFieldManager, true);

    G4cout << "Campo magnético configurado en el cilindro." << G4endl;

    G4cout << "Campo magnético en el cilindro configurado con componentes: "
           << "X = " << cylinderMagneticFieldVector.x()/tesla << " T, "
           << "Y = " << cylinderMagneticFieldVector.y()/tesla << " T, "
           << "Z = " << cylinderMagneticFieldVector.z()/tesla << " T." << G4endl;

    // Configura el campo electromagnético en el cilindro
    //G4ThreeVector electricFieldVector(0., 100.0 * volt/m, 0.); // Campo eléctrico en la dirección Y

    // Instancia de CylindricalEMFieldSetup para aplicar el campo al cilindro
    //cylEMFieldSetup = new CylindricalElectricFieldSetup(logicCylinder, electricFieldVector);

    
    
    // Define el vector del campo magnético en Tesla
    G4ThreeVector magneticFieldVector(1.0 * tesla, 0., 0.); // Campo magnético en la dirección Z

    // Crear una instancia de CylindricalMagneticFieldSetup para aplicar el campo magnético solo al cilindro
    fMagneticFieldSetup = new CylindricalMagneticFieldSetup(logicCylinder, magneticFieldVector);


    


    /*// Define el campo eléctrico uniforme
    cylinderElectricField = new G4UniformElectricField(G4ThreeVector(0.0, 100000.0 * kilovolt/cm, 0.0));

    // Define la ecuación de movimiento para el campo eléctrico
    G4EqMagElectricField* equation = new G4EqMagElectricField(cylinderElectricField);
    G4int nvar = 8;
    //G4ClassicalRK4* stepper = new G4ClassicalRK4(equation, nvar); // Cambia aquí al stepper deseado
    G4SimpleRunge* stepper = new G4SimpleRunge(equation);


    // Crea el FieldManager y el ChordFinder para el cilindro
    G4FieldManager* cylinderFieldManager = new G4FieldManager(cylinderElectricField);
    G4double minStep = 0.01 * mm;
    auto integrationDriver = new G4IntegrationDriver<G4SimpleRunge>(minStep, stepper, stepper->GetNumberOfVariables());
    G4ChordFinder* chordFinder = new G4ChordFinder(integrationDriver);
    cylinderFieldManager->SetChordFinder(chordFinder);
    // Asigna el FieldManager al volumen lógico del cilindro
    logicCylinder->SetFieldManager(cylinderFieldManager, true);

    G4cout << "Campo eléctrico configurado en el cilindro." << G4endl;

    G4cout << "Campo eléctrico en el cilindro configurado con componentes: "
           << "X = " << cylinderElectricFieldVector.x()/(volt/m) << " V/m, "
           << "Y = " << cylinderElectricFieldVector.y()/(volt/m) << " V/m, "
           << "Z = " << cylinderElectricFieldVector.z()/(volt/m) << " V/m." << G4endl;*/
    

    //Aquí es el mejor lugar para poder saber si las dimensiones del detector efectivamente cambian con geometry.mac o input.in
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

    // Aquí se puede verificar que las dimensiones del cilindro se hayan aplicado correctamente
    G4cout << "Cylinder size: Radius = " << cylinderRadius << " and Height =  " << cylinderHeight << G4endl;
    G4cout << "Cylinder position: X = " << cylinderPosX << ", Y = " << cylinderPosY << ", Z = " << cylinderPosZ << G4endl;  
}

MySensitiveDetector* MyDetectorConstruction::GetSensitiveDetector() const {
    return sensDet;
}

/*G4ThreeVector MyDetectorConstruction::GetMagneticFieldValue() const {
    return magneticFieldValue;
}*/

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