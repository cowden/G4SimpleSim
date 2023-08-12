
#ifndef FIBACTIONINITIALIZATION_H
#define FIBACTIONINITIALIZATION_H

#include "G4VUserActionInitialization.hh"

namespace fib {

class ActionInitialization: public G4VUserActionInitialization
{
    public:
    ActionInitialization();
    ~ActionInitialization() override;

    void BuildForMaster() const override;
    void Build() const override;

};
}

#endif
