#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4GenericMessenger.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SDManager.hh"
#include "G4GeometryManager.hh"
#include "CADMesh.hh"

class MyDetectorConstruction: public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

private:
    virtual void ConstructSDandField();

    void ConstructCherenkov(G4LogicalVolume* logicWorld);
    void ConstructScintillator(G4LogicalVolume* logicWorld);
    void ConstructCollimator(G4LogicalVolume* logicWorld);
    void ConstructDetector(G4LogicalVolume* logicWorld);
    void ConstructCalorimeter(G4LogicalVolume* logicWorld);
    void ConstructShield(G4LogicalVolume* logicWorld, G4String name);
    void ConstructControl(G4LogicalVolume* logicWorld);

    G4bool hasCalorimeter, hasShield, hasCollimator, hasScintillator, hasCherenkov, hasDetector;
    G4String shieldType;

    G4GenericMessenger* fMessenger;

    G4double xWorld;
    G4double yWorld;
    G4double zWorld;

    void DefineMaterials();
};

#endif // !CONSTRUCTION_HH