#ifndef FIBRUNACTION_H
#define FIBRUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

namespace fib {

class RunActionMessenger;

class RunAction: public G4UserRunAction
{
    public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    void SetFileName(G4String fn) { fileName_ = fn; }
    G4String GetFileName() { return fileName_; }

    private:
    RunActionMessenger * rm_;
    G4String fileName_;
};

}


#endif
