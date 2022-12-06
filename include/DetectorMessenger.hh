#pragma once

#include "G4UImessenger.hh"
#include "DetectorConstruction.hh"

class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

namespace B4c {

class DetectorMessenger: public G4UImessenger {
    public:
    DetectorMessenger(DetectorConstruction *);
    ~DetectorMessenger();

    void SetNewValue(G4UIcommand * command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

    private:
    DetectorConstruction * dc_;

    G4UIdirectory * dir_;
    G4UIcmdWithAnInteger * nLayerCmd_;
    G4UIcmdWithADoubleAndUnit * widthCmd_;
    G4UIcmdWithoutParameter * refreshCmd_;

};

}
