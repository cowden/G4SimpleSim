#ifndef FIBDETECTEDPHOTONHIT_H
#define FIBDETECTEDPHOTONHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4Threading.hh"
#include "G4ThreeVector.hh"

namespace fib {

class DetectedPhotonHit: public G4VHit
{
    public:
    DetectedPhotonHit();
    DetectedPhotonHit(const DetectedPhotonHit&) = default;
    DetectedPhotonHit(G4double t);
    ~DetectedPhotonHit() override;

    DetectedPhotonHit& operator=(const DetectedPhotonHit&) = default;
    G4bool operator==(const DetectedPhotonHit&) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    void Draw() override {}
    void Print() override;

    void SetTime(G4double t) { time_ = t; }
    G4double GetTime() const { return time_; }

    private:
    G4double time_;

};

typedef G4THitsCollection<DetectedPhotonHit> DetPhoHitsCollection;

extern G4ThreadLocal G4Allocator<DetectedPhotonHit>* DetPhoHitAllocator;

inline void* DetectedPhotonHit::operator new(size_t)
{
    if ( !DetPhoHitAllocator ) {
        DetPhoHitAllocator = new G4Allocator<DetectedPhotonHit>;
    }
    void *hit;
    hit = (void *) DetPhoHitAllocator->MallocSingle();
    return hit;
}

inline void DetectedPhotonHit::operator delete(void *hit)
{
    if ( !DetPhoHitAllocator ) {
        DetPhoHitAllocator = new G4Allocator<DetectedPhotonHit>;
    }
    DetPhoHitAllocator->FreeSingle((DetectedPhotonHit*) hit);
}



}

#endif
