#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"
#include "GeometrySize.hh"
#include "G4SystemOfUnits.hh"
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include "G4SystemOfUnits.hh"
#include <G4Tubs.hh>
#include "G4VSensitiveDetector.hh"
#include "G4RotationMatrix.hh"
#include "G4Material.hh"

using namespace CLHEP;

class DetectorConstruction : public G4VUserDetectorConstruction{
public:
  G4VPhysicalVolume* Construct() override;
  explicit DetectorConstruction(){
    InitializeMaterials();
  }
  //virtual ~DetectorConstruction();
private:
  G4Material * steel;
  G4Material * berillium;
  G4Material * XeCo2;
  G4Material * CO2;
  G4Material * xenon;
  G4Material * air;


  G4LogicalVolume * detector_logic;
  G4LogicalVolume * detector_logical;
  G4LogicalVolume * tube_with_hole_logic;
  G4LogicalVolume * cylinder_upper_logic;
  G4LogicalVolume * logicWorld;
  G4LogicalVolume * cylinder_cap_logic;
  G4LogicalVolume * cylinder_down_logic;
  G4LogicalVolume * cylinder_seccap_logic;
  G4LogicalVolume * window_logic;
  G4LogicalVolume * gas_logic;

  void InitializeMaterials();
  G4LogicalVolume * CreateDetector();
};
