#ifndef OTPRIMARYGENERATORACTION_HH
#define OTPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "OTMCEventGenerator.hh"

class OTPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    OTPrimaryGeneratorAction();    
    virtual ~OTPrimaryGeneratorAction();
    G4double kineticEnergy, ionCharge;

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    OTMCEventGenerator *fEventGenerator;
};

#endif
