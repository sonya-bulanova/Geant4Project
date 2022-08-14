#include <G4UserRunAction.hh>
//#include "TupleId.hh"
class G4Run; 

class RunAction : public G4UserRunAction{
public:
    RunAction();
    void BeginOfRunAction(const G4Run* aRun) override;
    void EndOfRunAction(const G4Run* aRun) override;
};

