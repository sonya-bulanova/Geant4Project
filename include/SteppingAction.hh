//SteppingAction.hh
#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"
#include "globals.hh"

class EventAction;

class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction* detectorConstruction, EventAction* eventAction);
  virtual ~SteppingAction();
  virtual void UserSteppingAction(const G4Step*);
private:
  EventAction*  fEventAction;
	DetectorConstruction* fDetConstruction;
};
