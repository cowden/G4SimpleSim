

#include "DetectorMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

namespace B4c {

DetectorMessenger::DetectorMessenger(DetectorConstruction * dc)
:G4UImessenger(), dc_(dc)
{
    dir_ = new G4UIdirectory("/det/");
    dir_->SetGuidance("Control detector construction parameters");

    nLayerCmd_ = new G4UIcmdWithAnInteger("/det/nLayers", this);
    nLayerCmd_->SetGuidance("Set the number of layers.");

    widthCmd_ = new G4UIcmdWithADoubleAndUnit("/det/width", this);
    widthCmd_->SetGuidance("Set the transverse width of detector.");

    refreshCmd_ = new G4UIcmdWithoutParameter("/det/refresh", this);
    refreshCmd_->SetGuidance("Cause DetectorConstruction to refresh geometry.");
}

DetectorMessenger::~DetectorMessenger()
{
    delete refreshCmd_;
    delete widthCmd_;
    delete nLayerCmd_;
    delete dir_;    
}

void DetectorMessenger::SetNewValue(G4UIcommand * command, G4String newValues )
{
    if ( command == nLayerCmd_ )
        dc_->SetNLayers( atoi(newValues) );
    else if ( command == widthCmd_ )
        dc_->SetWidth( widthCmd_->GetNewDoubleValue( newValues ) );
    else if ( command == refreshCmd_ )
        dc_->RefreshGeometry();
}

G4String DetectorMessenger::GetCurrentValue(G4UIcommand * command)
{
    G4String cv;
    if ( command == nLayerCmd_ )
        cv = nLayerCmd_->ConvertToString(dc_->GetNLayers());
    else if ( command == widthCmd_ )
        cv = widthCmd_->ConvertToString(dc_->GetWidth(), "cm");
    else if ( command == refreshCmd_ )
        cv = "";

    return cv;
}

}
