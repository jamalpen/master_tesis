#ifndef CYLINDRICAL_MAGNETIC_FIELD_SETUP_HH
#define CYLINDRICAL_MAGNETIC_FIELD_SETUP_HH

#include "G4UniformMagField.hh"
#include "G4EqMagElectricField.hh"
#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4DormandPrince745.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"

class CylindricalMagneticFieldSetup {
public:
    CylindricalMagneticFieldSetup(G4LogicalVolume* logicCylindricalVolume, G4ThreeVector magneticFieldVector);
    virtual ~CylindricalMagneticFieldSetup();

private:
    G4UniformMagField* fMagneticField;        // Campo magnético uniforme
    G4FieldManager* fFieldManager;            // Field manager para la región del cilindro

};

#endif // CYLINDRICAL_MAGNETIC_FIELD_SETUP_HH