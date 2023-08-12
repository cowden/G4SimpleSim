#ifndef FIBRUNACTIONMESSENGER_H
#define FIBRUNACTIONMESSENGER_H

#include "RunAction.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;

namespace fib {

class RunActionMessenger: public G4UImessenger {
    public:
    RunActionMessenger(RunAction * ra);
    ~RunActionMessenger();

    void SetNewValue(G4UIcommand *  command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand *command);

    private:
    RunAction * ra_;

    G4UIdirectory * dir_;
    G4UIcmdWithAString * nameCmd_;

};

}

#endif
