#ifndef CYLINDRICAL_ELECTRIC_FIELD_SETUP_HH
#define CYLINDRICAL_ELECTRIC_FIELD_SETUP_HH

#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"



class CylindricalElectricFieldSetup {
public:
    // Constructor: recibe el volumen lógico del cilindro y los vectores de campo
    CylindricalElectricFieldSetup(G4LogicalVolume* logicCylindricalVolume, 
                            G4ThreeVector electricFieldVector);
    
    // Destructor
    virtual ~CylindricalElectricFieldSetup();

private:
    // Campo electromagnético combinado
    G4UniformElectricField* fElectricField; // Campo eléctrico uniforme

    // Ecuación de movimiento para campos combinados
    G4EqMagElectricField* fEquation;

    // Field manager y chord finder para la región del cilindro
    G4FieldManager* fFieldManager;
    G4ChordFinder* fChordFinder;
};

#endif // CYLINDRICAL_EM_FIELD_SETUP_HH

