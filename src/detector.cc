#include "detector.hh"
#include "event.hh"

MySensitiveDetector::MySensitiveDetector(G4String name)
    : G4VSensitiveDetector(name)
{
    quEff = new G4PhysicsFreeVector();

    // std::ifstream datafile;
    // datafile.open("eff.dat");

    // while (1) {
    //     G4double wlen, eff;
    //     datafile >> wlen >> eff;
    //     if (datafile.eof()) break;
    //     quEff->InsertValues(wlen*nm, eff);
    //     G4cout << "Loaded efficiency data: wavelength = " << wlen << " nm, efficiency = " << eff << G4endl;
    // }

    // wlength bw 0.1 to 1 nm, step 0.01 nm
    // for (G4double i = 1; i < 10; i += 0.1) {
    //     G4double wlen = i * 0.1 * nm;
    //     quEff->InsertValues(wlen, 0.2);
    // }

    // datafile.close();
}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    G4Track* track = step->GetTrack();
    G4StepPoint* prePoint = step->GetPreStepPoint();
    const G4VTouchable* touchable = prePoint->GetTouchable();
    G4String volName = touchable->GetVolume()->GetName();
    G4String particleName = track->GetParticleDefinition()->GetParticleName();

    if (volName == "physCalorimeter") 
    {
        G4double edep = step->GetTotalEnergyDeposit();
        
        G4RunManager* runManager = G4RunManager::GetRunManager();
        MyEventAction* eventAction = (MyEventAction*)runManager->GetUserEventAction();
        eventAction->AddEdep(edep);

        return true;
    }

    G4StepPoint* postPoint = step->GetPostStepPoint();
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4int evt = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

    #ifndef G4MULTITHREADED
        G4cout << "Detector position: " << posDetector << G4endl;
        G4cout << "Hit in volume: " << volName << ", particle: " << particleName << G4endl;
    #endif

    if (particleName == "gamma") {
        track->SetTrackStatus(fStopAndKill);
    }

    G4ThreeVector posParticle = prePoint->GetPosition();
    G4double energy = postPoint->GetKineticEnergy();
    G4ThreeVector momParticle = postPoint->GetMomentum();

    analysisManager->FillNtupleIColumn(0, 0, evt);
    analysisManager->FillNtupleDColumn(0, 1, posParticle.x());
    analysisManager->FillNtupleDColumn(0, 2, posParticle.y());
    analysisManager->FillNtupleDColumn(0, 3, posParticle.z());
    analysisManager->FillNtupleDColumn(0, 4, energy);
    analysisManager->FillNtupleDColumn(0, 5, momParticle.mag());
    analysisManager->AddNtupleRow(0);

    return true;
}
