#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <fstream>
#include <vector>

class SteppingAction : public G4UserSteppingAction
{
public:
   SteppingAction();
   virtual ~SteppingAction();

   virtual void UserSteppingAction(const G4Step* step);

private:
   std::ofstream outFile; // Output file stream
   G4double fTrackLength; // Length of the track
   G4double fStepInterval; // Interval at which to print track information

   struct StepData {
       G4int stepNumber;
       G4double x, y, z;
       G4double kineticEnergy;
       G4double energyDeposit;
       G4double stepLength;
       G4double trackLength;
       G4String nextVolumeName;
       G4String processName;
   };

   std::vector<StepData> stepData; // Vector to store step data
};

#endif

