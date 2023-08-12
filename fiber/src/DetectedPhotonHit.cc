
#include "DetectedPhotonHit.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<fib::DetectedPhotonHit>* fib::DetPhoHitAllocator = nullptr;

fib::DetectedPhotonHit::DetectedPhotonHit()
:time_(0)
{}

fib::DetectedPhotonHit::DetectedPhotonHit(G4double t)
:time_(t)
{}

fib::DetectedPhotonHit::~DetectedPhotonHit()
{}

G4bool fib::DetectedPhotonHit::operator==(const fib::DetectedPhotonHit& right) const
{
    return (this == &right) ? true : false;
}

void fib::DetectedPhotonHit::Print()
{
}
