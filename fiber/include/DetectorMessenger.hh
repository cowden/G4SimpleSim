#ifndef FIBDETECTORMESSENGER_H
#define FIBDETECTORMESSENGER_H

#include "G4UImessenger.hh"
#include "DetectorConstruction.hh"

class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

namespace fib {

class DetectorMessenger: public G4UImessenger
{
    public:
    DetectorMessenger(DetectorConstruction *);
    ~DetectorMessenger();

    void SetNewValue(G4UIcommand * command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand *command);

    private:
    DetectorConstruction * dc_;

    G4UIdirectory *dir_;
    G4UIcmdWithADouble * nCoreCmd_;
    G4UIcmdWithADouble * nCladCmd_;
    G4UIcmdWithADouble * nGlassCmd_;
    G4UIcmdWithADoubleAndUnit * rCoreCmd_;
    G4UIcmdWithADoubleAndUnit * rCladCmd_;
    G4UIcmdWithADoubleAndUnit * lengthCmd_;
    G4UIcmdWithADoubleAndUnit * absCoreCmd_;
    G4UIcmdWithADoubleAndUnit * absCladCmd_;
    
};

}

#endif
