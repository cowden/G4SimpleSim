#ifndef FIBTRACKINGACTION_H
#define FIBTRACKINGACTION_H

#include "G4UserTrackingAction.hh"

namespace fib {

class TrackingAction: public G4UserTrackingAction
{
    public:
    TrackingAction();
    ~TrackingAction() override;

    virtual void PreUserTrackingAction( const G4Track*);
    virtual void PostUserTrackingAction(const G4Track *) { }

};
}

#endif
