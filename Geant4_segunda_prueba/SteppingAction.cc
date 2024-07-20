#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include <algorithm>

SteppingAction::SteppingAction() : G4UserSteppingAction(), fTrackLength(0.), fStepInterval(1.*m)
{
    // Open the file in append mode
    outFile.open("track_info.txt", std::ios::out | std::ios::app);
    // Write the header to the file
    outFile << std::setw(5) << "Step#" << std::setw(12) << "X(m)"
            << std::setw(12) << "Y(m)" << std::setw(12) << "Z(m)"
            << std::setw(12) << "KinE(MeV)" << std::setw(12) << "dE(MeV)"
            << std::setw(12) << "StepLeng(m)" << std::setw(12) << "TrackLeng(m)"
            << std::setw(15) << "NextVolume" << std::setw(15) << "ProcName" << G4endl;
}

SteppingAction::~SteppingAction() 
{
    // Close the file
    outFile.close();
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Accumulate track length
    fTrackLength += step->GetStepLength();

    // Get the track
    G4Track* track = step->GetTrack();

    // Get step information
    StepData data;
    data.stepNumber = track->GetCurrentStepNumber();
    G4ThreeVector position = step->GetPostStepPoint()->GetPosition();
    data.x = position.x() / m;
    data.y = position.y() / m;
    data.z = position.z() / m;
    data.kineticEnergy = step->GetPostStepPoint()->GetKineticEnergy() / MeV;
    data.energyDeposit = step->GetTotalEnergyDeposit() / MeV;
    data.stepLength = step->GetStepLength() / m;
    data.trackLength = track->GetTrackLength() / m;
    data.nextVolumeName = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();
    data.processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

    // Store step information in the vector
    stepData.push_back(data);

    // Check if we have reached the interval
    if (fTrackLength >= fStepInterval)
    {
        // Sort step data by step number
        std::sort(stepData.begin(), stepData.end(), [](const StepData& a, const StepData& b) {
            return a.stepNumber < b.stepNumber;
        });

        // Write step information to the file in meters
        for (const auto& step : stepData) {
            outFile << std::setw(5) << step.stepNumber
                    << std::setw(12) << step.x
                    << std::setw(12) << step.y
                    << std::setw(12) << step.z
                    << std::setw(12) << step.kineticEnergy
                    << std::setw(12) << step.energyDeposit
                    << std::setw(12) << step.stepLength
                    << std::setw(12) << step.trackLength
                    << std::setw(15) << step.nextVolumeName
                    << std::setw(15) << step.processName
                    << G4endl;
        }

        // Clear the vector for the next interval
        stepData.clear();

        // Reset track length for the next interval
        fTrackLength = 0.;
    }
}

