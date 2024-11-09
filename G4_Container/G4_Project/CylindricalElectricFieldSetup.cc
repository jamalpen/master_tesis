#include "CylindricalElectricFieldSetup.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4TransportationManager.hh"
#include "G4LogicalVolume.hh"

// Constructor: Inicializa el campo eléctrico y magnético en el volumen lógico del cilindro
CylindricalElectricFieldSetup::CylindricalElectricFieldSetup(G4LogicalVolume* logicCylindricalVolume, 
                                                 G4ThreeVector electricFieldVector)
{
    
    // Crear el campo eléctrico
    fElectricField = new G4UniformElectricField(electricFieldVector);

    // Configurar la ecuación de movimiento para el campo eléctrico
    fEquation = new G4EqMagElectricField(fElectricField);

    // Crear el Field Manager y Chord Finder para el campo combinado
    fFieldManager = new G4FieldManager();
    fFieldManager->SetDetectorField(fElectricField);

    // Crear el stepper con el método Runge-Kutta Dormand-Prince
    G4int nvar = 8;  // Número de variables
    auto pStepper = new G4ClassicalRK4(fEquation, nvar);

    // Configurar el driver de integración
    G4double minStep = 10 * mm; // Paso mínimo de integración
    auto pIntegrationDriver = new G4IntegrationDriver<G4ClassicalRK4>(minStep, pStepper, nvar);

    fChordFinder = new G4ChordFinder(pIntegrationDriver);

    // Configurar el Field Manager para usar el Chord Finder y el campo combinado
    fFieldManager->SetChordFinder(fChordFinder);

    // Crear una región para el cilindro y asignar el Field Manager a esta región
    G4Region* cylindricalRegion = new G4Region("CylindricalRegion");
    cylindricalRegion->AddRootLogicalVolume(logicCylindricalVolume);
    cylindricalRegion->SetFieldManager(fFieldManager);
}

// Destructor: Libera la memoria de los objetos creados
CylindricalElectricFieldSetup::~CylindricalElectricFieldSetup()
{
    delete fElectricField;
    delete fEquation;
    delete fFieldManager;
    delete fChordFinder;
}


