#include "OTMCEventGenerator.hh"
#include "globals.hh"
#include "TString.h"
 
OTMCEventGenerator::OTMCEventGenerator(TString fileName) {
  fInputFile.open(fileName.Data());
  fInputFile >> fNumEvents;
}
 
OTMCEventGenerator::~OTMCEventGenerator() {
  if(fInputFile.is_open()) fInputFile.close();
}
 
bool OTMCEventGenerator::ReadNextEvent(Double_t &vx, Double_t &vy, Double_t &vz) {
  G4int eventID;
  if (!(fInputFile >> eventID >> fNumTracks >> vx >> vy >> vz))
    return false;
 
  fCurrentTrackID = 0;
  return true;
}
 
bool OTMCEventGenerator::ReadNextTrack(Int_t &Z, Int_t &N, Double_t &px, Double_t &py, Double_t &pz) {
  if (fCurrentTrackID >= fNumTracks)
    return false;
 
  fInputFile >> Z  >> N >> px >> py >> pz;
  fCurrentTrackID++;
 
  return true;
}
