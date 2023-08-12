
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"


fib::ActionInitialization::ActionInitialization()
{}

fib::ActionInitialization::~ActionInitialization()
{}

void fib::ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction);
}

void fib::ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
}
