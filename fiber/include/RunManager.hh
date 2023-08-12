#ifndef FIBRUNMANAGER_H
#define FIBRUNMANAGER_H

#include "G4MTRunManager.hh"
#include "globals.hh"

namespace fib {

class RunManagerMessenger;

class RunManager: public G4MTRunManager {
    public:
    RunManager();
    ~RunManager();

    void SetSeed(G4int sd) { seed_ = sd; }
    G4int GetSeed() { return seed_; }

    protected:
    virtual G4bool InitializeSeeds(G4int nevnts);

    private:
    RunManagerMessenger * msngr_;
    G4int seed_;
};

}

#endif
