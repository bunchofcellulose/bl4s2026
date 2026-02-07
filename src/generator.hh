#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGeneratorAction();
    ~MyPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

private:
    G4GeneralParticleSource* fParticleGun;
};

#endif