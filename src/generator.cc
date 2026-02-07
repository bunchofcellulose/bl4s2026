#include "generator.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
    fParticleGun = new G4GeneralParticleSource();
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}