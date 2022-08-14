//ActionInitialization.cc
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
//#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction *fDetConstruction)
 : G4VUserActionInitialization(),
  DetConstruction(fDetConstruction)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{}

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new RunAction());
  auto eventAction = new EventAction();
	SetUserAction(eventAction);
  SetUserAction(new SteppingAction(DetConstruction, eventAction));
}  
