#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

class MyRunAction : public G4UserRunAction {
public:
    MyRunAction();
    virtual ~MyRunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    G4AnalysisManager* analysisManager;
};

#endif // !RUN_HH