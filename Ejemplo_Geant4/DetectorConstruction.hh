// DetectorConstruction.hh
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
   DetectorConstruction();
   virtual ~DetectorConstruction();

   virtual G4VPhysicalVolume* Construct();
};

#endif


