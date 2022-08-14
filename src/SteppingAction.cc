#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Event.hh"
#include "G4VPhysicalVolume.hh"

SteppingAction::SteppingAction(DetectorConstruction* detectorConstruction, EventAction* eventAction)
        : G4UserSteppingAction(),
          fDetConstruction(detectorConstruction),
          fEventAction(eventAction){}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* aStep){
    if (aStep->GetTrack()->GetVolume()->GetName() == "gas") {
      G4double energy_negative = (aStep->GetTotalEnergyDeposit() / keV);
      fEventAction -> AddEdep(energy_negative);
  }
}
