
#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorMessenger.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4GeometryManager.hh"

#include "G4SDManager.hh"
#include "GlassSD.hh"

fib::DetectorConstruction::DetectorConstruction()
:constructed_(false), nCore_(1.457), nClad_(1.42),
nGlass_(1.517), rCore_(0.3*mm), rClad_(0.33*mm),
l_(1*m), absCore_(28.1*m), absClad_(28.1*m)
{
    msngr_ = new DetectorMessenger(this);
}

fib::DetectorConstruction::~DetectorConstruction()
{
    delete msngr_;
}

void fib::DetectorConstruction::SetNcore(G4double n)
{
    nCore_ = n;
}

void fib::DetectorConstruction::SetNclad(G4double n)
{
    nClad_ = n;
}

void fib::DetectorConstruction::SetNglass(G4double n)
{
    nGlass_ = n;
}

void fib::DetectorConstruction::SetRcore(G4double r)
{
    rCore_ = r;
}

void fib::DetectorConstruction::SetRclad(G4double r)
{
    rClad_ = r;
}

void fib::DetectorConstruction::SetLength(G4double l)
{
    l_ = l;
}

void fib::DetectorConstruction::SetAbsCore(G4double a)
{
    absCore_ = a;
}

void fib::DetectorConstruction::SetAbsClad(G4double a)
{
    absClad_ = a;
}

G4VPhysicalVolume* fib::DetectorConstruction::Construct()
{
    DefineMaterials();

    return DefineVolumes();
}

void fib::DetectorConstruction::DefineMaterials()
{

    auto nistManager = G4NistManager::Instance();

  // Air
  // 
    nistManager->FindOrBuildMaterial("G4_AIR");

    // quartz fused silica, silcon-dioxide
    //nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    auto Si = nistManager->FindOrBuildElement("Si");
    auto O = nistManager->FindOrBuildElement("O");
    auto core = new G4Material("Core", 2.2*g/cm3, 2);
    core->AddElement(Si, 1);
    core->AddElement(O, 2);

    auto clad = new G4Material("Clad", 2.2*g/cm3, 2);
    clad->AddElement(Si, 1);
    clad->AddElement(O, 2);

    // glass
    nistManager->FindOrBuildMaterial("G4_Pyrex_Glass");

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;



  //
  // ------------ Generate & Add Material Properties Table ------------
  //
  const G4int nEntries = 32;

  G4double PhotonEnergy[nEntries] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };


  //
  // Air
  //
  G4double RefractiveIndex2[nEntries] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);
  
  G4Material::GetMaterial("G4_AIR")->SetMaterialPropertiesTable(myMPT2);


  // ------------- Surfaces and Optical Properties --------------
  const unsigned nEnergies = 3;
  G4double energies[nEnergies] = { 1.625*eV, 5.*eV, 12.4*eV };
  G4double qRindex[nEnergies] = {nCore_, nCore_, nCore_};   
  G4double qAbsLength[nEnergies] = {absCore_, absCore_, absCore_};

  G4MaterialPropertiesTable *qProps = new G4MaterialPropertiesTable();
  qProps->AddProperty("RINDEX",energies,qRindex,nEnergies);
  qProps->AddProperty("ABSLENGTH",energies,qAbsLength,nEnergies);
  core->SetMaterialPropertiesTable(qProps);

  G4double cRindex[nEnergies] = {nClad_,nClad_,nClad_};
  G4double cAbsLength[nEnergies] = {absClad_,absClad_,absClad_};
  
  G4MaterialPropertiesTable *cProps = new G4MaterialPropertiesTable();
  cProps->AddProperty("RINDEX",energies,cRindex,nEnergies);
  cProps->AddProperty("ABSLENGTH",energies,cAbsLength,nEnergies);
  clad->SetMaterialPropertiesTable(cProps);


  G4double gRindex[nEnergies] = {1.47, 1.47, 1.47};
  G4double gAbsLength[nEnergies] = {absCore_, absCore_, absCore_};

  G4MaterialPropertiesTable *gProps = new G4MaterialPropertiesTable();
  gProps->AddProperty("RINDEX",energies,gRindex, nEnergies);
  gProps->AddProperty("ABSLENGTH",energies,gAbsLength,nEnergies);
  G4Material::GetMaterial("G4_Pyrex_Glass")->SetMaterialPropertiesTable(gProps);

}

G4VPhysicalVolume* fib::DetectorConstruction::DefineVolumes()
{
    constructed_ = true;

    // compute geometrical parameters
    G4double l2 = l_/2.;
    G4double worldSizeXY = 1.2*rClad_;
    G4double worldSizeZ = l_ + 10*cm;


    // get materials from store
    auto air = G4Material::GetMaterial("G4_AIR");
    auto glass = G4Material::GetMaterial("G4_Pyrex_Glass");
    auto coremat = G4Material::GetMaterial("Core");
    auto cladmat = G4Material::GetMaterial("Clad");

    // construct world
    worldS_ = new G4Tubs("World",
                         0., worldSizeXY, worldSizeZ/2.,
                         0., twopi);
    worldLV_ = new G4LogicalVolume(
                    worldS_,
                    air,
                    "World");
    worldPV_ = new G4PVPlacement(
                    0,                 // no rotation
                    G4ThreeVector(),    // at (0,0,0)
                    worldLV_,           // its logical volume
                    "World",            // its name
                    0,                  // its mother volume
                    false,              // no boolean operation
                    0,                  // copy number
                    checkOverlaps_);    // checking overlaps


    // cladding
    cladS_ = new G4Tubs("Clad",
                    0., rClad_, l2,
                    0., twopi);
    cladLV_ = new G4LogicalVolume(
                    cladS_,
                    cladmat,
                    "Clad");
    cladPV_ = new G4PVPlacement(
                    0,
                    G4ThreeVector(),
                    cladLV_,
                    "Clad",
                    worldLV_,
                    false,
                    0,
                    checkOverlaps_);

    // core
    coreS_ = new G4Tubs("Core",
                    0., rCore_, l2,
                    0., twopi);
    coreLV_ = new G4LogicalVolume(
                    coreS_,
                    coremat,
                    "Core");
    corePV_ = new G4PVPlacement(
                    0,
                    G4ThreeVector(),
                    coreLV_,
                    "Core",
                    cladLV_,
                    false,
                    0,
                    checkOverlaps_);

    // glass
    glassS_ = new G4Tubs("Glass",
                   0., rClad_, 1*mm,
                   0., twopi);
    glassLV_ = new G4LogicalVolume(
                    glassS_,
                    glass,
                    "Glass");
    glassPV_ = new G4PVPlacement(
                    0,
                    G4ThreeVector(0., 0., l2+1*mm),
                    glassLV_,
                    "Glass",
                    worldLV_,
                    false,
                    0,
                    checkOverlaps_); 

    //
    // Always return the physical World
    //
    return worldPV_;

}


void fib::DetectorConstruction::ConstructSDandField()
{
    // 
    // Sensitive detectors
    //
    //glassSD_ = new fib::GlassSD("GlassSD", "GlassHitsCollection");
    //G4SDManager::GetSDMpointer()->AddNewDetector(glassSD_);
    //SetSensitiveDetector("Glass", glassSD_);
}

void fib::DetectorConstruction::ClearPhysicalVolumes()
{
    assert( constructed_ );

    delete corePV_;
    delete cladPV_;
    delete glassPV_;
    delete worldPV_;

    coreLV_->ClearDaughters();
    cladLV_->ClearDaughters();
    glassLV_->ClearDaughters();
    worldLV_->ClearDaughters();

}

void fib::DetectorConstruction::ClearLogicalVolumes()
{
    assert( constructed_ );

    delete coreLV_;
    delete cladLV_;
    delete glassLV_;
    delete worldLV_;

}

void fib::DetectorConstruction::ClearSensitiveDetectors()
{
    assert( constructed_ );
    delete glassSD_;
}

void fib::DetectorConstruction::RefreshGeometry()
{
    G4GeometryManager::GetInstance()->OpenGeometry();

    ClearPhysicalVolumes();
    ClearLogicalVolumes();
    ClearSensitiveDetectors();

    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    constructed_ = false;

    G4RunManager::GetRunManager()->ReinitializeGeometry(true);
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    G4RunManager::GetRunManager()->InitializeGeometry();
}
