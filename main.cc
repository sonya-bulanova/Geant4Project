#include <DetectorConstruction.hh>
#include "ActionInitialization.hh"
#include <QGSP_BERT.hh>
#include <G4VisManager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <RunAction.hh>
#include <random>
#include "G4RunManager.hh"
#include "G4ScoringManager.hh"

using namespace CLHEP;

int main(int argc, char **argv) {
    std::random_device rd;
    std::uniform_int_distribution<long> uid(0, LONG_MAX);
    long seed = uid(rd);
    HepRandom::setTheSeed(seed);
    //std::cout<<"Seed "<<seed<<std::endl;
    G4UIExecutive *ui = nullptr;
    if(argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    //TupleId *tuple = new TupleId();
	DetectorConstruction *geom = new DetectorConstruction();
  auto runManager = new G4RunManager;
	G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
  runManager->SetUserInitialization(new QGSP_BERT());
  runManager->SetUserInitialization(geom);
	auto actionInitialization = new ActionInitialization(geom);
	runManager->SetUserInitialization(actionInitialization);
  runManager->Initialize();

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialise();

    auto UImanager = G4UImanager::GetUIpointer();

    if(!ui) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
   } else {
        UImanager->ApplyCommand("/control/execute start0.mac");
        ui->SessionStart();
       delete ui;
    }
    delete visManager;
    delete runManager;
}
