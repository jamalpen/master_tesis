// Geant libraries
//
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "g4root.hh"
#include "Randomize.hh"
#include "G4ios.hh"

// Local libraries
//
#include "PrimarySpectrum.hh"
//#include "EventAction.hh"
#include "PrimarySpectrumMessenger.hh"

// C++ libraries
//
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>

PrimarySpectrum::PrimarySpectrum():
    pi(3.14159265358979323846), lineNumber(0)
{
    // Here I modify for the initial position of the particle.
    particlePosition = G4ThreeVector(0., 0., 400.*cm);
    particleDirection = G4ThreeVector(0., 0., -1.);

    fSpectMessenger = new PrimarySpectrumMessenger(this);
    inputFile = new char();
    //inputFile = "pao-fluxSec-dec2006.shw.bz2";

    //openFile(inputFile);

    initx = 0.*m;
    inity = 0.*m;
    initz = 1.5*m;
    areaDimX = 1.0*km; // Ejemplo de dimensión inicial en X
    areaDimY = 1.0*km; // Ejemplo de dimensión inicial en Y
    areaDimZ = 1.0*km; // Ejemplo de dimensión inicial en Z
    r = 0.;
    theta = 0.;
    px = 0.*GeV;
    py = 0.*GeV;
    pz = 0.*GeV;
}

PrimarySpectrum::~PrimarySpectrum()
{}

int PrimarySpectrum::openFile(std::string name)
{
    char tmpc[256];
    const char* nfi = name.c_str();

    snprintf(tmpc, 256, "bzip2 -d -c %s", nfi);
    inFile = popen(tmpc, "r");

    G4cout << "File was opened" << G4endl;

    return 1;
}

void PrimarySpectrum::primaryMomento()
{
    G4int search = 1;
    char line[256];


    while (search)
    { 
        if (feof(inFile))

        openFile(inputFile);

        if (fgets(line, 256, inFile))
        {
            lineNumber++;
            std::cout << "Numero de linea: " << lineNumber << std::endl;
            // Saltar las primeras 5 líneas
            if (lineNumber <= 5)
                continue;
                
            // Comprobar si la línea es un comentario o resumen
            if (line[0] == '#' || feof(inFile))
                break;

            if (line[0] != '#')
            {   
                sscanf(line, "%d %lf %lf %lf %lf %lf %lf %d %d %lf %lf %lf\n",
                       &crkId, &px, &py, &pz, &x, &y, &z, &shwId, &prmId, &prmEner, &prmThe, &prmPhi);
                std::cout << "El numero de la linea que se analizo es: " << lineNumber << std::endl;
                std::cout << "Linea: " << line << std::endl;
            }
        }

        search = 0;

        switch (crkId)
        {
            case 1:
                parId = "gamma";
                break;
            case 2:
                parId = "e+";
                break;
            case 3:
                parId = "e-";
                break;
            case 5:
                parId = "mu+";
                break;
            case 6:
                parId = "mu-";
                break;
            case 7:
                parId = "pi0";
                break;
            case 8:
                parId = "pi+";
                break;
            case 9:
                parId = "pi-";
                break;
            case 10:
                parId = "kaon0L";
                break;
            case 11:
                parId = "kaon+";
                break;
            case 12:
                parId = "kaon-";
                break;
            case 13:
                parId = "neutron";
                break;
            case 14:
                parId = "proton";
                break;
            case 15:
                parId = "anti_proton";
                break;
            case 25:
                parId = "anti_neutron";
                break;
            default:
                search = 1;
        }
    }

    particleDirection = G4ThreeVector(px * GeV, py * GeV, -1. * (pz * GeV));
    particlePosition = G4ThreeVector(x * m, y * m, z * m); // Update position particle with input.in file
    G4cout << "Dirección de la partícula: " << particleDirection << G4endl;
    G4cout << "Posición de la partícula: " << particlePosition << G4endl;
    G4cout << "El ID de la particula es: " << parId << G4endl;
}

void PrimarySpectrum::primaryPosition()
{
    //initx = (G4UniformRand() - 0.5) * areaDimX;
    //inity = (G4UniformRand() - 0.5) * areaDimY;
    //initz = (G4UniformRand() - 0.5) * areaDimZ;

    //particlePosition = G4ThreeVector(initx, inity, initz);

    //G4cout << "Posición de la partícula: " << particlePosition << G4endl;
}

void PrimarySpectrum::setInitPosX(G4double xx)
{
    this->initx = xx;
}

void PrimarySpectrum::setInitPosY(G4double yy)
{
    this->inity = yy;
}

void PrimarySpectrum::setInitPosZ(G4double zz)
{
    this->initz = zz;
}

void PrimarySpectrum::setAreaDimX(G4double dimX)
{
    this->areaDimX = dimX;
}

void PrimarySpectrum::setAreaDimY(G4double dimY)
{
    this->areaDimY = dimY;
}

void PrimarySpectrum::setAreaDimZ(G4double dimZ)
{
    this->areaDimZ = dimZ;
}


G4double PrimarySpectrum::getEnergy() const
{
    return prmEner;
}
