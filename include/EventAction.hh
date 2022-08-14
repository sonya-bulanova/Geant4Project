//EventAction.hh
#include <G4VSensitiveDetector.hh>
#include "g4analysis.hh"
#include "TupleId.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction{
public:
  EventAction();
  virtual ~EventAction();

  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);
  G4double energy_negative;
  void AddEdep(G4double energy) { energy_negative += energy; }
};
