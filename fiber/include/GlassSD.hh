#ifndef FIBGLASSSD_H
#define FIBGLASSSD_H

#include "G4VSensitiveDetector.hh"

#include "DetectedPhotonHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

namespace fib {

class GlassSD: public G4VSensitiveDetector
{
    public:
    GlassSD(const G4String & name,
            const G4String & hitsCollectionName);
    ~GlassSD() override;

    void Initialize(G4HCofThisEvent* hitCollection) override;
    G4bool ProcessHits(G4Step *step, G4TouchableHistory* history) override;
    void EndOfEvent(G4HCofThisEvent* hitCollection) override;

    private:
    DetPhoHitsCollection* hitsCollection_ = nullptr;

};

}

#endif
