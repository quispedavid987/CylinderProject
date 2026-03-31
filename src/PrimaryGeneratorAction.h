#ifndef PRIMARY_GENERATOR_ACTION_HH
#define PRIMARY_GENERATOR_ACTION_HH 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4VUserActionInitialization.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
MyActionInitialization();
~MyActionInitialization();
virtual void Build() const;

};


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

private:
    G4ParticleGun* fParticleGun;
};
#endif
