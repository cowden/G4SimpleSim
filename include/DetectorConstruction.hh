//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file DetectorConstruction.hh
/// \brief Definition of the B4c::DetectorConstruction class

#ifndef B4cDetectorConstruction_h
#define B4cDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;
class G4Box;
class G4PVReplica;
class G4LogicalVolume;

namespace B4c
{

class DetectorMessenger;
class CalorimeterSD;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of CalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.
/// In addition a transverse uniform magnetic field is defined
/// via G4GlobalMagFieldMessenger class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

  public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    void SetNLayers(G4int n);
    void SetWidth(G4double w);

    G4int GetNLayers() { return fNofLayers; }
    G4double GetWidth() { return fWidth; }

    void RefreshGeometry();

  private:
    bool constructed_;
    DetectorMessenger * msngr_;
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    void ClearPhysicalVolumes();
    void ClearLogicalVolumes();
    void ClearSensitiveDetectors();

    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
                                      // magnetic field messenger

    G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
    G4int  fNofLayers = -1;     // number of layers
    G4double fWidth;

    G4Box * worldS_;
    G4LogicalVolume * worldLV_;
    G4VPhysicalVolume * worldPV_;

    G4Box * calorimeterS_;
    G4LogicalVolume * calorLV_;
    G4VPhysicalVolume * calorPV_;

    G4Box * layerS_;
    G4LogicalVolume * layerLV_;
    G4PVReplica * layerPV_;

    G4Box * absorberS_;
    G4LogicalVolume * absorberLV_;
    G4VPhysicalVolume * absorberPV_;

    G4Box * gapS_;
    G4LogicalVolume * gapLV_;
    G4VPhysicalVolume * gapPV_;

    CalorimeterSD * absoSD_;
    CalorimeterSD * gapSD_;

};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

