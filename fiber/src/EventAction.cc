
#include "EventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "G4SDManager.hh"
#include "G4Event.hh"
#include "GlassSD.hh"
#include "G4HCofThisEvent.hh"

fib::EventAction::EventAction()
{}

fib::EventAction::~EventAction()
{}

void fib::EventAction::PrintEventStatistics() const
{}

void fib::EventAction::BeginOfEventAction(const G4Event *)
{ }

void fib::EventAction::EndOfEventAction(const G4Event * event)
{
    // Fill histograms, nutple
    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // get primary particle
    auto primary = event->GetPrimaryVertex()->GetPrimary();

    // fill ntuple
    auto hcid = G4SDManager::GetSDMpointer()->GetCollectionID("GlassHitsCollection");
    auto hc = static_cast<DetPhoHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcid)); 
    for ( unsigned i=0; i != hc->GetSize(); i++ ) {
        auto hit = (*hc)[i];
        analysisManager->FillNtupleDColumn(0, 0, hit->GetTime() );
        analysisManager->AddNtupleRow(0);
    }
}
