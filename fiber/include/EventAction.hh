#ifndef FIBEVENTACTION_H
#define FIBEVENTACTION_H

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace fib {

class EventAction: public G4UserEventAction
{
    public:
    EventAction();
    ~EventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    private:
    void PrintEventStatistics() const;
    // return hit collection

    // data members
};
}

#endif
