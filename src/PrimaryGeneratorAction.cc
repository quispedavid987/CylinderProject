#include "PrimaryGeneratorAction.h"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

MyActionInitialization::MyActionInitialization() {}
MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const{
PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
SetUserAction(generator);
}


PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1); // disparar 1 particulas

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable(); // llamando a la lista de particulas
    G4ParticleDefinition* particle = particleTable -> FindParticle("mu-"); // definiendo el proton

    fParticleGun -> SetParticleDefinition(particle);
    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
    fParticleGun -> SetParticleEnergy(60. * MeV);
    fParticleGun -> SetParticlePosition(G4ThreeVector(0., 0., 45. * cm));
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun -> GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
delete fParticleGun;
}