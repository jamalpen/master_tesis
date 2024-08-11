#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    
    /* Se pone aquí ahora en el constructor en vez de la función de más abajo llamado 
    MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
    debido a que lo que queremos es modificar siempre los parámetros
    iniciales de la partícula. Es decir sobreescribir los datos iniciales 
    de la partícula con los macro files*/
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");
    
    G4ThreeVector pos(0.,0.,0.);
    G4ThreeVector mom(0.,0.,1.);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100.*GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
