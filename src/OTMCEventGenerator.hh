#ifndef OTMCEVENTGENGENERATOR_HH
#define OTMCEVENTGENGENERATOR_HH
 
#include <fstream>
#include "globals.hh"
#include "TString.h"
 
class OTMCEventGenerator {
  public:
    OTMCEventGenerator(TString fileName);
    virtual ~OTMCEventGenerator();
   
    bool ReadNextEvent(G4double &vx, G4double &vy, G4double &vz);
    bool ReadNextTrack(G4int &Z, G4int &N, G4double &px, G4double &py, G4double &pz);
 
    G4int GetNumEvents() { return fNumEvents; };
 
  private:
    std::ifstream fInputFile;
    G4int fNumEvents;
    G4int fNumTracks;
    G4int fCurrentTrackID;
};
 
#endif
