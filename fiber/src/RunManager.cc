
#include "RunManager.hh"

#include "RunManagerMessenger.hh"

fib::RunManager::RunManager()
:G4MTRunManager()
{
    msngr_ = new RunManagerMessenger(this);
}

fib::RunManager::~RunManager()
{
    delete msngr_;
}

G4bool fib::RunManager::InitializeSeeds(G4int nevnts) {
    auto helper = G4RNGHelper::GetInstance();
    helper->Clear();

    for ( unsigned i=0; i != 2*nevnts; i++ )
        helper->AddOneSeed(seed_+i*2);

    return true;
}
