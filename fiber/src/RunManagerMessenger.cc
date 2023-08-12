
#include "RunManagerMessenger.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

fib::RunManagerMessenger::RunManagerMessenger(fib::RunManager *rm)
:G4UImessenger(), rm_(rm)
{
    dir_ = new G4UIdirectory("/rm/");
    dir_->SetGuidance("Control RunManager");

    seedCmd_ = new G4UIcmdWithAnInteger("/rm/seed", this);
    seedCmd_->SetGuidance("Set the starting seed for the RNG.");
}

fib::RunManagerMessenger::~RunManagerMessenger()
{
    delete seedCmd_;
    delete dir_;
}

void fib::RunManagerMessenger::SetNewValue(G4UIcommand * cmd, G4String sval)
{
    if ( cmd == seedCmd_ )
        rm_->SetSeed( atoi(sval) );
}

G4String fib::RunManagerMessenger::GetCurrentValue(G4UIcommand *cmd)
{
    G4String cv;
    if ( cmd == seedCmd_ )
        cv = seedCmd_->ConvertToString(rm_->GetSeed());

    return cv;
}
