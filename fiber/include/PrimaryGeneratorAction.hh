#ifndef FIBPRIMARYGENERATORACTION_H
#define FIBPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;

namespace fib {

class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
    public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* event) override;

    void SetImpactParameter(G4double b ) { b_ = b; }
    G4double GetImpactParameter() const { return b_; }

    void SetAlpha(G4double a) { a_ = a; }
    G4double GetAlpha() const { return a_; }

    private:
    PrimaryGeneratorMessenger * pgm_;
    G4ParticleGun* particleGun_ = nullptr;

    G4double a_;
    G4double b_;

};
}

#endif
