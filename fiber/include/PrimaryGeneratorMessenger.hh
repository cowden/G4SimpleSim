#ifndef FIBPRIMARYGENERATORMESSENGER_H
#define FIBPRIMARYGENERATORMESSENGER_H

#include "PrimaryGeneratorAction.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

namespace fib {

class PrimaryGeneratorMessenger: public G4UImessenger {
    public:
    PrimaryGeneratorMessenger(fib::PrimaryGeneratorAction * pg);
    ~PrimaryGeneratorMessenger();

    void SetNewValue(G4UIcommand *, G4String );
    G4String GetCurrentValue(G4UIcommand *);

    private:
    PrimaryGeneratorAction * pg_;

    G4UIdirectory * dir_;
    G4UIcmdWithADoubleAndUnit * bCmd_;
    G4UIcmdWithADouble * aCmd_;
};

}

#endif
