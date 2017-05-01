#include "OTSteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

OTSteppingAction::OTSteppingAction()
: G4UserSteppingAction()
{
}

OTSteppingAction::~OTSteppingAction()
{
}

void OTSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
  G4int volumeID = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetCopyNo();
  G4double totalEdep = step -> GetTotalEnergyDeposit();
  G4int pdg = step -> GetTrack() -> GetParticleDefinition() -> GetPDGEncoding();
  G4ThreeVector position = step -> GetPreStepPoint() -> GetPosition();
  G4int parentID = step -> GetTrack() -> GetParentID();
  G4int trackID = step -> GetTrack() -> GetTrackID();


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> FillNtupleIColumn(0, eventID);
  analysisManager -> FillNtupleIColumn(1, volumeID);
  analysisManager -> FillNtupleDColumn(2, totalEdep);
  analysisManager -> FillNtupleIColumn(3, pdg);
  analysisManager -> FillNtupleDColumn(4, position.x());
  analysisManager -> FillNtupleDColumn(5, position.y());
  analysisManager -> FillNtupleDColumn(6, position.z());
  analysisManager -> FillNtupleIColumn(7, parentID);
  analysisManager -> FillNtupleIColumn(8, trackID);
  analysisManager -> AddNtupleRow();
}
