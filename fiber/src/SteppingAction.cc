#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4OpticalPhoton.hh"
#include "G4AnalysisManager.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"

fib::SteppingAction::SteppingAction()
{ }

void fib::SteppingAction::UserSteppingAction(const G4Step * step )
{
    auto particleDef = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition();
    if ( particleDef == G4OpticalPhoton::OpticalPhotonDefinition() ) {
        auto preVol = step->GetPreStepPoint()->GetPhysicalVolume();
        auto postVol = step->GetPostStepPoint()->GetPhysicalVolume();
        if ( (preVol->GetName() == "Core" || preVol->GetName() == "Clad") && postVol->GetName() == "Glass" ) {
            auto analysisManager = G4AnalysisManager::Instance();
            auto evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
            analysisManager->FillNtupleIColumn(1, 0, evID);
            analysisManager->FillNtupleDColumn(1, 1, step->GetPostStepPoint()->GetGlobalTime());
            analysisManager->AddNtupleRow(1);

            step->GetTrack()->SetTrackStatus(fStopAndKill);
        }
    }
}
