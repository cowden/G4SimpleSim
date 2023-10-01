
#include "GlassSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4OpticalPhoton.hh"

#include "G4VProcess.hh"
#include "G4Track.hh"

fib::GlassSD::GlassSD(const G4String& name, const G4String& hitsCollectionName)
:G4VSensitiveDetector(name)
{
    collectionName.insert(hitsCollectionName);
}

fib::GlassSD::~GlassSD()
{ }

void fib::GlassSD::Initialize(G4HCofThisEvent* hce)
{
    hitsCollection_ = new fib::DetPhoHitsCollection(SensitiveDetectorName, collectionName[0]);

    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection( hcID, hitsCollection_ );

    hitsCollection_->insert(new DetectedPhotonHit());
}

G4bool fib::GlassSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    if ( step->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition() )
        return false;

    auto touchable = step->GetPostStepPoint()->GetTouchable();
    auto vol1 = step->GetPreStepPoint()->GetPhysicalVolume();

    if ( step->IsFirstStepInVolume() ) {
        DetectedPhotonHit * hit = new DetectedPhotonHit(step->GetPreStepPoint()->GetGlobalTime());
        hitsCollection_->insert(hit);
    }

    
    return true;
}

void fib::GlassSD::EndOfEvent(G4HCofThisEvent*)
{
    if ( verboseLevel>1 ){
        G4int nHits = hitsCollection_->GetSize();
        G4cout << G4endl
        << "=========> " << nHits << " photons detected" << G4endl;
    }
}
