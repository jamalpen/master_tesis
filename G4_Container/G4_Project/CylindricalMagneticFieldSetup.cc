#include "CylindricalMagneticFieldSetup.hh"
#include "G4Region.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"

// Constructor: Inicializa el campo magnético en el volumen lógico del cilindro
CylindricalMagneticFieldSetup::CylindricalMagneticFieldSetup(G4LogicalVolume* logicCylindricalVolume, 
                                                             G4ThreeVector magneticFieldVector)
{
    // Crear el campo magnético
    fMagneticField = new G4UniformMagField(magneticFieldVector);

    // Crear un Field Manager específico para la región del cilindro
    fFieldManager = new G4FieldManager();
    fFieldManager->SetDetectorField(fMagneticField);

    // Crear el Chord Finder para el Field Manager del cilindro
    fFieldManager->CreateChordFinder(fMagneticField);

    // Asignar el Field Manager al volumen lógico del cilindro
    G4Region* cylindricalRegion = new G4Region("CylindricalRegion");
    cylindricalRegion->AddRootLogicalVolume(logicCylindricalVolume);
    cylindricalRegion->SetFieldManager(fFieldManager);
}

// Destructor: Liberar la memoria asignada
CylindricalMagneticFieldSetup::~CylindricalMagneticFieldSetup()
{
    delete fMagneticField;
    delete fFieldManager;
}