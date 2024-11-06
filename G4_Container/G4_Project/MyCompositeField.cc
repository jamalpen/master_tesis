#include "MyCompositeField.hh"

MyCompositeField::MyCompositeField(const G4ThreeVector& magneticFieldVector, const G4ThreeVector& electricFieldVector)
{
    magneticField = new G4UniformMagField(magneticFieldVector);
    electricField = new G4UniformElectricField(electricFieldVector);
}

MyCompositeField::~MyCompositeField()
{
    delete magneticField;
    delete electricField;
}

void MyCompositeField::GetFieldValue(const G4double point[4], G4double* field) const
{
    // Obtener los componentes del campo magnético
    G4double magField[3] = {0., 0., 0.};
    magneticField->GetFieldValue(point, magField);

    // Obtener los componentes del campo eléctrico
    G4double elecField[3] = {0., 0., 0.};
    electricField->GetFieldValue(point, elecField);

    // Combina los campos en el array de salida
    field[0] = elecField[0];
    field[1] = elecField[1];
    field[2] = elecField[2];
    field[3] = magField[0];
    field[4] = magField[1];
    field[5] = magField[2];
}
