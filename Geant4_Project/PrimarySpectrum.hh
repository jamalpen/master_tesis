/* I will use this file to define all the parameters of my
.shw.bz2 file, which is provided by CORSIKA within the ARTI platform */

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

    void primaryMomento();
    int openFile(std::string name);
    
    G4ThreeVector getPosition() const;// no se creo ni se uso
    G4ThreeVector getDirection() const;//no se creo ni se uso
    G4String getParticleId() const; // no se definio ni se uso
    G4double getEnergy() const; //Solo se uso este metodo

    G4ThreeVector particlePosition;
    G4ThreeVector particleDirection;
    G4String parId;
    std::string inputFile; //[] = "tmpMachin24h.shw.bz2"
    
private:
    G4double pi;
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

    G4int lineNumber;
};

#endif
