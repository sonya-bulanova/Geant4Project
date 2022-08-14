#include "RunAction.hh"
#include "g4analysis.hh"
#include <G4VSensitiveDetector.hh>
#include "TupleId.hh"

using namespace CLHEP;

RunAction::RunAction()
 : G4UserRunAction()
{}

void RunAction::BeginOfRunAction(const G4Run *aRun) {
  G4AnalysisManager *analysisManager = G4Analysis::ManagerInstance("root");
  analysisManager->OpenFile("Run_20keV");
	analysisManager -> CreateNtuple("electrons", "electrons");
	analysisManager -> CreateNtupleDColumn("total_energy_deposit");
	analysisManager -> FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run *aRun) {
  G4UserRunAction::EndOfRunAction(aRun);
  G4AnalysisManager* analysisManager = G4Analysis::ManagerInstance("root");
  analysisManager -> Write();
  analysisManager -> CloseFile(true);
}
