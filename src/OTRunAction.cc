#include "OTRunAction.hh"
#include "g4root.hh"
#include "G4RootAnalysisManager.hh"

OTRunAction::OTRunAction()
: G4UserRunAction()
{
}

OTRunAction::~OTRunAction()
{
  delete G4RootAnalysisManager::Instance();
}

void OTRunAction::BeginOfRunAction(const G4Run*)
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  analysisManager -> OpenFile("data");

  analysisManager -> CreateNtuple("step", "step");
  analysisManager -> CreateNtupleIColumn("eventID");
  analysisManager -> CreateNtupleIColumn("volumeID");
  analysisManager -> CreateNtupleDColumn("edep");
  analysisManager -> CreateNtupleIColumn("pdg");
  analysisManager -> CreateNtupleDColumn("position_x");
  analysisManager -> CreateNtupleDColumn("position_y");
  analysisManager -> CreateNtupleDColumn("position_z");
  analysisManager -> CreateNtupleIColumn("parentID");
  analysisManager -> CreateNtupleIColumn("trackID");
  analysisManager -> FinishNtuple();
}

void OTRunAction::EndOfRunAction(const G4Run*)
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  analysisManager -> Write();
  analysisManager -> CloseFile();
}
