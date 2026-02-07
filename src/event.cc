#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*) {
    fEdep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(1, 0, fEdep);
    analysisManager->AddNtupleRow(1);

    #ifndef G4MULTITHREADED
        G4cout << "Total energy deposited: " << fEdep << G4endl;
    #endif
}
