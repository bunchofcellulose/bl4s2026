#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"
#include "QGSP_BERT.hh"
// #include "G4OpticalPhysics.hh"

#include "construction.hh"
#include "action.hh"
#include "generator.hh"

int main(int argc, char** argv)
{
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager();
        runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif

    runManager->SetUserInitialization(new MyDetectorConstruction());
    
    G4VModularPhysicsList* physList = new QGSP_BERT;
    // physList->RegisterPhysics(new G4OpticalPhysics());
    runManager->SetUserInitialization(physList);

    runManager->SetUserInitialization(new MyActionInitialization());

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        G4UIExecutive *ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute mac/vis.mac");
        ui->SessionStart();
    } else {
        G4String command = "/control/execute mac/";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    return 0;
}