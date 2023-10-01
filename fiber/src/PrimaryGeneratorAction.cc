
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "globals.hh"

fib::PrimaryGeneratorAction::PrimaryGeneratorAction()
:a_(CLHEP::pi/3), b_(0.)
{
    pgm_ = new PrimaryGeneratorMessenger(this);

    G4int nParticles = 1;
    particleGun_ = new G4ParticleGun(nParticles);

    auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
    particleGun_->SetParticleDefinition(particleDefinition);
    particleGun_->SetParticleMomentumDirection(G4ThreeVector(1., 1., 1.));
    particleGun_->SetParticleEnergy(5.*MeV);

}

fib::PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete pgm_;
    delete particleGun_;
}

void fib::PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Tubs * worldtub = dynamic_cast<G4Tubs*>(worldLV->GetSolid());
  G4double c_ = worldtub->GetOuterRadius();

  G4cout << "  ParticleGun angle: " << a_ << " impact parameter: " << b_ << G4endl;

   particleGun_->SetParticleMomentumDirection(G4ThreeVector(0., sin(a_), cos(a_)));
   particleGun_->SetParticlePosition(G4ThreeVector(b_, -c_, -c_/tan(a_)));
   particleGun_->GeneratePrimaryVertex(anEvent); 
}
