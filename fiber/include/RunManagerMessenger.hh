#ifndef FIBRUNMANAGERMESSENGER_H
#define FIBRUNMANAGERMESSENGER_H

#include "G4UImessenger.hh"
#include "RunManager.hh"

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

namespace fib {

class RunManagerMessenger: public G4UImessenger {
    public:
    RunManagerMessenger(RunManager *);
    ~RunManagerMessenger();

    void SetNewValue(G4UIcommand * command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

    private:
    RunManager * rm_;

    G4UIdirectory *dir_;
    G4UIcmdWithAnInteger * seedCmd_;

};

}

#endif
