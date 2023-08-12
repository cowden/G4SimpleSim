
#include "DetectorMessenger.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

fib::DetectorMessenger::DetectorMessenger(fib::DetectorConstruction *dc)
:G4UImessenger(), dc_(dc)
{
    dir_ = new G4UIdirectory("/det/");
    dir_->SetGuidance("Control detector geometry");

    nCoreCmd_ = new G4UIcmdWithADouble("/det/nCore", this);
    nCoreCmd_->SetGuidance("Set the core index of refraction.");

    nCladCmd_ = new G4UIcmdWithADouble("/det/nClad", this);
    nCladCmd_->SetGuidance("Set the clad index of refraction.");

    nGlassCmd_ = new G4UIcmdWithADouble("/det/nGlass", this);
    nGlassCmd_->SetGuidance("Set the glass index of refraction.");

    rCoreCmd_ = new G4UIcmdWithADoubleAndUnit("/det/rCore", this);
    rCoreCmd_->SetGuidance("Set the core radius.");

    rCladCmd_ = new G4UIcmdWithADoubleAndUnit("/det/rClad", this);
    rCladCmd_->SetGuidance("Set the clad radius.h");

    lengthCmd_ = new G4UIcmdWithADoubleAndUnit("/det/length", this);
    lengthCmd_->SetGuidance("Set the length of the fiber.");

    absCoreCmd_ = new G4UIcmdWithADoubleAndUnit("/det/absCore", this);
    absCoreCmd_->SetGuidance("Set the absorption length of the core material.");

    absCladCmd_ = new G4UIcmdWithADoubleAndUnit("/det/absClad", this);
    absCladCmd_->SetGuidance("Set the absorption length of the clad material.");
}

fib::DetectorMessenger::~DetectorMessenger()
{
    delete nCoreCmd_;
    delete nCladCmd_;
    delete nGlassCmd_;
    delete rCoreCmd_;
    delete rCladCmd_;
    delete lengthCmd_;
    delete absCoreCmd_;
    delete absCladCmd_;
    delete dir_; 
}

void fib::DetectorMessenger::SetNewValue(G4UIcommand * command, G4String value)
{
    if ( command == nCoreCmd_ )
        dc_->SetNcore( nCoreCmd_->GetNewDoubleValue(value) );
    else if ( command == nCladCmd_ )
        dc_->SetNclad( nCladCmd_->GetNewDoubleValue(value) );
    else if ( command == nGlassCmd_ )
        dc_->SetNglass( nGlassCmd_->GetNewDoubleValue(value) );
    else if ( command == rCoreCmd_ )
        dc_->SetRcore( rCoreCmd_->GetNewDoubleValue(value) );
    else if ( command == rCladCmd_ ) 
        dc_->SetRclad( rCladCmd_->GetNewDoubleValue(value) );
    else if ( command == lengthCmd_ )
        dc_->SetLength( lengthCmd_->GetNewDoubleValue(value) );
    else if ( command == absCoreCmd_ )
        dc_->SetAbsCore( absCoreCmd_->GetNewDoubleValue(value) );
    else if ( command == absCladCmd_ )
        dc_->SetAbsClad( absCladCmd_->GetNewDoubleValue(value) );
}

G4String fib::DetectorMessenger::GetCurrentValue(G4UIcommand * command)
{
    G4String cv;
    if ( command == nCoreCmd_ )
        cv = nCoreCmd_->ConvertToString(dc_->GetNcore());
    else if ( command == nCladCmd_ )
        cv = nCladCmd_->ConvertToString(dc_->GetNclad());
    else if ( command == nGlassCmd_ )
        cv = nGlassCmd_->ConvertToString(dc_->GetNglass());
    else if ( command == rCoreCmd_ )
        cv = rCoreCmd_->ConvertToStringWithBestUnit(dc_->GetRcore());
    else if ( command == rCladCmd_ )
        cv = rCladCmd_->ConvertToStringWithBestUnit(dc_->GetRclad());
    else if ( command == lengthCmd_ )
        cv = lengthCmd_->ConvertToStringWithBestUnit(dc_->GetLength());
    else if ( command == absCoreCmd_ )
        cv = absCoreCmd_->ConvertToStringWithBestUnit(dc_->GetAbsCore());
    else if ( command == absCladCmd_ )
        cv = absCladCmd_->ConvertToStringWithBestUnit(dc_->GetAbsClad());

    return cv;
}
