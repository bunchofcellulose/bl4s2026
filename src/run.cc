#include "run.hh"

MyRunAction::MyRunAction()
{
    analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->CreateNtuple("Hits", "Hits Data");
    analysisManager->CreateNtupleIColumn("fEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->CreateNtupleDColumn("fE");
    analysisManager->CreateNtupleDColumn("fp");
    analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Calorimeter", "Calorimeter Data");
    analysisManager->CreateNtupleDColumn("fEdep");
    analysisManager->FinishNtuple(1);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4int runNumber = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runNumber;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}