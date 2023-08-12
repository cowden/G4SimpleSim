#include "PrimaryGeneratorMessenger.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"

fib::PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(fib::PrimaryGeneratorAction *pg)
:G4UImessenger(), pg_(pg)
{
    dir_ = new G4UIdirectory("/pg/");
    dir_->SetGuidance("Control primary generator");

    bCmd_ = new G4UIcmdWithADoubleAndUnit("/pg/impact", this);
    bCmd_->SetGuidance("Set the impact parameter.");

    aCmd_ = new G4UIcmdWithADouble("/pg/alpha", this);
    aCmd_->SetGuidance("Set the longitudinal angle.");

}

fib::PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
    delete aCmd_;
    delete bCmd_;
    delete dir_;

}

void fib::PrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command, G4String value)
{
    if ( command == bCmd_ )
        pg_->SetImpactParameter( bCmd_->GetNewDoubleValue(value) );
    else if ( command == aCmd_ )
        pg_->SetAlpha( aCmd_->GetNewDoubleValue(value) );
}

G4String fib::PrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command )
{
    G4String cv;
    if ( command == bCmd_ )
        cv = bCmd_->ConvertToString(pg_->GetImpactParameter());
    else if ( command == aCmd_ )
        cv = aCmd_->ConvertToString(pg_->GetAlpha());

    return cv;
}
