#include "EventAction.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "G4Gamma.hh"
#include "G4VProcess.hh"
#include "G4TrackingManager.hh"

EventAction::EventAction()
	: G4UserEventAction()
{}
EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *event) {
		energy_negative = 0;
}

void EventAction::EndOfEventAction(const G4Event *event) {
    auto analysisManager = G4AnalysisManager::Instance();
    auto id = event -> GetEventID();
		if(energy_negative != 0){
			analysisManager->FillNtupleDColumn(0, 0, energy_negative +
				CLHEP::RandGauss::shoot(0., 0.035131325053291 * energy_negative));
			analysisManager->AddNtupleRow(0);
    }
}
