
#include "RunAction.hh"
#include "RunActionMessenger.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

fib::RunAction::RunAction()
{
    rm_ = new RunActionMessenger(this);

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true);

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);

  // Creating ntuple
  //
  //analysisManager->CreateNtuple("fib", "photons");
  //analysisManager->CreateNtupleDColumn("time");
  //analysisManager->FinishNtuple();

  // create ntuple of created photons in quartz
  //
  analysisManager->CreateNtuple("quartz","photons");
  analysisManager->CreateNtupleDColumn("time");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->FinishNtuple();

  // create ntuple of photons crossing into pmt
  //
  analysisManager->CreateNtuple("pmt", "photons");
  analysisManager->CreateNtupleIColumn("event");
  analysisManager->CreateNtupleDColumn("time");
  analysisManager->FinishNtuple();
}

fib::RunAction::~RunAction()
{
    delete rm_;
}

void fib::RunAction::BeginOfRunAction(const G4Run *)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  analysisManager->OpenFile(fileName_);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void fib::RunAction::EndOfRunAction(const G4Run * )
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
