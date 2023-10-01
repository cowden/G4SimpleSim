#ifndef FIBSTEPPINGACTION_H
#define FIBSTEPPINGACTION_H

#include "G4UserSteppingAction.hh"

class G4Step;

namespace fib {

class SteppingAction: public G4UserSteppingAction
{
    public:
    SteppingAction();
    ~SteppingAction() { }

    virtual void UserSteppingAction(const G4Step *);

};
}

#endif
