//ActionInitialization.hh

#include "G4VUserActionInitialization.hh"
//#include "DetectorConstruction.hh"

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    explicit ActionInitialization(DetectorConstruction*);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
  private:
	DetectorConstruction *DetConstruction;
};
