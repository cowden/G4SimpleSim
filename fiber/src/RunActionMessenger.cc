
#include "RunActionMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"

fib::RunActionMessenger::RunActionMessenger(RunAction * ra)
:G4UImessenger(), ra_(ra)
{
    dir_ = new G4UIdirectory("/runaction/", this);
    dir_->SetGuidance("Control the RunAction.");

    nameCmd_ = new G4UIcmdWithAString("/runaction/fileName", this);
    nameCmd_->SetGuidance("Set the output file name.");
}

fib::RunActionMessenger::~RunActionMessenger()
{
    delete nameCmd_;
    delete dir_;
}

void fib::RunActionMessenger::SetNewValue(G4UIcommand * command, G4String newValues)
{
    if ( command == nameCmd_ )
        ra_->SetFileName(newValues);
}

G4String fib::RunActionMessenger::GetCurrentValue(G4UIcommand * command)
{
    G4String cv;
    if ( command == nameCmd_ )
        cv = ra_->GetFileName();

    return cv;
}
