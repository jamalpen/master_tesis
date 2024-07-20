///////////////////////////////////
////////PrimarySpectrum.hh/////////
///////////////////////////////////

#ifndef PrimarySpectrum_HH
#define PrimarySpectrum_HH

// Geant4 Libraries
#include "globals.hh"
#include "G4ThreeVector.hh"

// C++ Libraries
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <iomanip>

class PrimarySpectrumMessenger;

class PrimarySpectrum
{
public:
    PrimarySpectrum();
    ~PrimarySpectrum();

    void primaryPosition();
    void primaryMomento();
    int openFile(std::string name);
    
    void setInitPosX(G4double xx);
    void setInitPosY(G4double yy);
    void setInitPosZ(G4double zz);
    void setAreaDimX(G4double dimX);
    void setAreaDimY(G4double dimY);
    void setAreaDimZ(G4double dimZ);
    
    G4ThreeVector getPosition() const;
    G4ThreeVector getDirection() const;
    G4String getParticleId() const;
    G4double getEnergy() const; // Nuevo getter

    G4ThreeVector particlePosition;
    G4ThreeVector particleDirection;
    G4String parId;
    std::string inputFile; //[] = "tmpMachin24h.shw.bz2"
    //G4double Ro; // This can be omitted if not needed for paralelepiped
    
private:
    G4double pi;
    G4double initx;
    G4double inity;
    G4double initz;
    G4double areaDimX;
    G4double areaDimY;
    G4double areaDimZ;
    float r;
    float theta;

    G4int crkId;
    G4double px;
    G4double py;
    G4double pz;
    G4double x;
    G4double y;
    G4double z;
    G4int shwId;
    G4int prmId;
    G4double prmEner;
    G4double prmThe;
    G4double prmPhi;

    FILE *inFile = NULL;
    PrimarySpectrumMessenger* fSpectMessenger;
};

#endif
