#include "DetectorConstruction.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    G4double world_sizeXYZ = 30 * cm;

    auto solidWorld =
            new G4Box("World",
                      0.5 * world_sizeXYZ,
                      0.5 * world_sizeXYZ,
                      0.5 * world_sizeXYZ);

    logicWorld =
            new G4LogicalVolume(solidWorld,
                                air,
                                "World");

    auto physWorld =
            new G4PVPlacement(0,
                               G4ThreeVector(0, 0, 0),
                               logicWorld,
                               "World",
                               0,
                               false,
                               0,
                               checkOverlaps);

    detector_logic = CreateDetector();
    return physWorld;
}

G4LogicalVolume* DetectorConstruction::CreateDetector() {
  //rotation matrix (for cylinder and window)
  G4RotationMatrix * rotm = new G4RotationMatrix();
  rotm -> rotateZ(-18.20835*deg);
  G4RotationMatrix * rotwin = new G4RotationMatrix();
  rotwin -> rotateZ(18.2083*deg);

auto cylinder_upper_solid =
        new G4Tubs("cylinder",
                   0.5 * hole_diameter,
                   0.5 * cylinder_diameter,
                   0.5 * hole_lenght,
                   0,
                   2 * pi);

  cylinder_upper_logic =
          new G4LogicalVolume(cylinder_upper_solid,
                              steel,
                              "cylinder_upper");

  auto cylinder_upper_phys =
          new G4PVPlacement(0,
                            G4ThreeVector(0, 0, -30 * mm),
                            cylinder_upper_logic,
                            "cylinder_upper",
                            logicWorld,
                            false,
                            0);

 //cylinder hat:
 auto cylinder_cap_solid =
         new G4Tubs("cylinder",
                    0,
                    0.5 * cylinder_diameter,
                    0.5 * (cylinder_lenght - hole_lenght),
                    0,
                    2 * pi);

 cylinder_cap_logic =
         new G4LogicalVolume(cylinder_cap_solid,
                             steel,
                             "cylinder_cap");

 auto cylinder_cap_phys =
         new G4PVPlacement(0,
                           G4ThreeVector(0, 0, -50 * mm),
                           cylinder_cap_logic,
                           "cylinder_cap",
                           logicWorld,
                           false,
                           0);

//part of cylinder with Be-window
    auto tube_with_hole_solid =
            new G4Tubs("tube_with_hole",
                       0.5 * hole_diameter,
                       0.5 * cylinder_diameter,
                       0.5 * empty_length,
                       0,
                       323.5833 * degree);

    tube_with_hole_logic =
            new G4LogicalVolume(tube_with_hole_solid,
                                steel,
                                "tube_with_hole");

    auto tube_with_hole_phys =
            new G4PVPlacement(rotm,
                              G4ThreeVector(0, 0, 0),
                              tube_with_hole_logic,
                              "tube_with_hole",
                              logicWorld,
                              false,
                              0);

  auto cylinder_down_solid =
          new G4Tubs("cylinder",
                     0.5 * hole_diameter,
                     0.5 * cylinder_diameter,
                     0.5 * hole_lenght,
                     0,
                     2 * pi);

    cylinder_down_logic =
            new G4LogicalVolume(cylinder_down_solid,
                                steel,
                                "cylinder_down");

    auto cylinder_down_phys =
            new G4PVPlacement(0,
                              G4ThreeVector(0, 0, 30 * mm),
                              cylinder_down_logic,
                              "cylinder_down",
                              logicWorld,
                              false,
                              0);

  //one more hat
  auto cylinder_seccap_solid =
          new G4Tubs("cylinder",
                     0,
                     0.5 * cylinder_diameter,
                     0.5 * (cylinder_lenght - hole_lenght),
                     0,
                     2 * pi);

  cylinder_seccap_logic =
          new G4LogicalVolume(cylinder_seccap_solid,
                              steel,
                              "cylinder_seccap");

  auto cylinder_seccap_phys =
          new G4PVPlacement(0,
                            G4ThreeVector(0, 0, 50 * mm),
                            cylinder_seccap_logic,
                            "cylinder_seccap",
                            logicWorld,
                            false,
                            0);
  //Be-window
  auto window_solid =
          new G4Tubs("window",
                      0.5 * hole_diameter - wind_thick,
                      0.5 * hole_diameter,
                      0.5 * empty_length,
                      0,
                      (360 - 323.5833) * degree);

  window_logic =
          new G4LogicalVolume(window_solid,
                              berillium,
                              "window");

  auto window_phys =
          new G4PVPlacement(rotwin,
                            G4ThreeVector(1 * mm, 0, 0),
                            window_logic,
                            "window",
                            logicWorld,
                            false,
                            0);
  //Gas geometry:
  auto gas_solid =
          new G4Tubs("gas",
                      0,
                      0.5 * full_diameter,
                      0.5 * full_lengh,
                      0,
                      2*pi);

  gas_logic =
          new G4LogicalVolume(gas_solid,
                              XeCo2,
                              "gas");

  auto gas_phys =
          new G4PVPlacement(0,
                            G4ThreeVector(0, 0, 0),
                            gas_logic,
                            "gas",
                            logicWorld,
                            false,
                            0);

  return gas_logic;
}

void DetectorConstruction::InitializeMaterials() {
    auto nist = G4NistManager::Instance();
    steel = nist -> FindOrBuildMaterial("G4_STAINLESS-STEEL");
    berillium = nist -> FindOrBuildMaterial("G4_Be");
    xenon = nist -> FindOrBuildMaterial("G4_Xe");
    air = nist -> FindOrBuildMaterial("G4_AIR");

    G4Element * oxygen =  new G4Element("Oxygen", "O", 8., 16.00*g/mole);
    G4Element * carbon =  new G4Element("Carbon", "C", 6., 12.00*g/mole);

    double co2_density = 0.60232 * kg/m3;
    double density = 2.3996 * kg/m3;

    CO2 = new G4Material("CO2", co2_density, 2);
    CO2 -> AddElement(oxygen, 2);
    CO2 -> AddElement(carbon, 1);

    XeCo2 = new G4Material("XeCo2", density, 2);
    XeCo2 -> AddMaterial(CO2, 5*perCent);
    XeCo2 -> AddMaterial(xenon, 95*perCent);
}
