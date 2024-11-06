#ifndef MYCOMPOSITEFIELD_HH
#define MYCOMPOSITEFIELD_HH

#include "G4ElectroMagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4UniformElectricField.hh"
#include "G4ThreeVector.hh"

class MyCompositeField : public G4ElectroMagneticField {
public:
    MyCompositeField(const G4ThreeVector& magneticFieldVector, const G4ThreeVector& electricFieldVector);
    virtual ~MyCompositeField();

    virtual void GetFieldValue(const G4double point[4], G4double* field) const override;

    // Implementa DoesFieldChangeEnergy
    virtual G4bool DoesFieldChangeEnergy() const override {
        return false; // Esto puede ser true o false según el comportamiento que necesites.
    }

private:
    G4UniformMagField* magneticField;
    G4UniformElectricField* electricField;
};

#endif