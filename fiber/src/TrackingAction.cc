#include "TrackingAction.hh"
#include "G4AnalysisManager.hh"
#include "G4OpticalPhoton.hh"

#include "G4Track.hh"

fib::TrackingAction::TrackingAction() { }

fib::TrackingAction::~TrackingAction()
{ }

void fib::TrackingAction::PreUserTrackingAction(const G4Track* track)
{

    if ( track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() ) {
        if ( track->GetVolume()->GetName() == "Core"  || track->GetVolume()->GetName() == "Clad" ) {
           auto analysisManager = G4AnalysisManager::Instance();
           analysisManager->FillNtupleDColumn(0, 0, track->GetGlobalTime());
           analysisManager->FillNtupleDColumn(0, 1, track->GetPosition().z());
           analysisManager->AddNtupleRow(0);
        }
    }

}

