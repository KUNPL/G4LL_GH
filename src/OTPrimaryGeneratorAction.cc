#include "OTPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "OTMCEventGenerator.hh"

OTPrimaryGeneratorAction::OTPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
//  fEventGenerator = new OTMCEventGenerator("/Users/hwan/tools/opentutorials_Geant4/AMD.gen");

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4IonTable* ionTable = G4IonTable::GetIonTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable -> FindParticle(particleName = "proton");
//  G4ParticleDefinition* ion
//    = ionTable -> GetIon(3,7,0);

  //fParticleGun -> SetParticleDefinition(particle);
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun -> SetParticleDefinition(particle);
  ionCharge = 0.*eplus; 
  kineticEnergy = G4UniformRand()*600.*MeV;
/*
  if(G4UniformRand()<=0.5)
  {
    fParticleGun -> SetParticleDefinition(particle);
    kineticEnergy = G4UniformRand()*600*MeV;
  }
  else if(G4UniformRand()>0.5)
  {
    fParticleGun -> SetParticleDefinition(particle);
    kineticEnergy = (G4UniformRand()-0.5)*600*MeV;
  }
*/
  fParticleGun -> SetParticleCharge(ionCharge); 
  fParticleGun -> SetParticleEnergy(kineticEnergy);
}

void OTPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) 
  {
    fParticleGun -> GeneratePrimaryVertex(anEvent);
  }

OTPrimaryGeneratorAction::~OTPrimaryGeneratorAction()
{
  delete fParticleGun;
}

