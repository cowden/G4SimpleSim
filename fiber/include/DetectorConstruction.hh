#ifndef FIBDETECTORCONSTRUCTION_H
#define FIBDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4Tubs;
class G4LogicalVolume;

namespace fib {

class DetectorMessenger;
class GlassSD;

class DetectorConstruction: public G4VUserDetectorConstruction
{
    public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    // set parameters of the geometry
    void SetNcore(G4double);
    void SetNclad(G4double);
    void SetNglass(G4double);
    void SetRcore(G4double);
    void SetRclad(G4double);
    void SetLength(G4double);
    void SetAbsCore(G4double);
    void SetAbsClad(G4double);

    G4double GetNcore() { return nCore_; }
    G4double GetNclad() { return nClad_; }
    G4double GetNglass() { return nGlass_; }
    G4double GetRcore() { return rCore_; }
    G4double GetRclad() { return rClad_; }
    G4double GetLength() { return l_; }
    G4double GetAbsCore() { return absCore_; }
    G4double GetAbsClad() { return absClad_; }

    void RefreshGeometry();

    private:
    bool constructed_;
    DetectorMessenger * msngr_;

    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    void ClearPhysicalVolumes();
    void ClearLogicalVolumes();
    void ClearSensitiveDetectors();

    G4bool checkOverlaps_ = true;
    G4double nCore_;
    G4double nClad_;
    G4double nGlass_;
    G4double rCore_;
    G4double rClad_;
    G4double l_;
    G4double absCore_;
    G4double absClad_;

    G4Tubs *worldS_;
    G4LogicalVolume *worldLV_;
    G4VPhysicalVolume *worldPV_;

    G4Tubs *coreS_;
    G4LogicalVolume *coreLV_;
    G4VPhysicalVolume *corePV_;

    G4Tubs *cladS_;
    G4LogicalVolume *cladLV_;
    G4VPhysicalVolume *cladPV_;

    G4Tubs * glassS_;
    G4LogicalVolume * glassLV_;
    G4VPhysicalVolume * glassPV_;

    // sensitive detectors
    GlassSD * glassSD_;

};

}

#endif
