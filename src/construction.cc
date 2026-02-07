#include "construction.hh"
#include "detector.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    fMessenger = new G4GenericMessenger(this, "/MyDetector/", "Detector construction control");

    fMessenger->DeclareProperty("hasCalorimeter", hasCalorimeter = true, "Include calorimeter");
    fMessenger->DeclareProperty("hasShield", hasShield = true, "Include shield");
    fMessenger->DeclareProperty("hasCollimator", hasCollimator = false, "Include collimator");
    fMessenger->DeclareProperty("hasScintillator", hasScintillator = false, "Include scintillator");
    fMessenger->DeclareProperty("hasCherenkov", hasCherenkov = false, "Include Cherenkov");
    fMessenger->DeclareProperty("hasDetector", hasDetector = true, "Include photon detector");
    fMessenger->DeclareProperty("shieldType", shieldType = "schwarzD.stl", "Shield type STL file");

    xWorld = 0.5 * m;
    yWorld = 0.5 * m;
    zWorld = 1.5 * m;

    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    // World
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    worldMat->SetName("Air");

    // Aerogel Setup
    G4Material *SiO2 = new G4Material("SiO2", 2.201 * g / cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
    G4Material *H2O = new G4Material("H2O", 1.000 * g / cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);
    G4Element *C = nist->FindOrBuildElement("C");
    G4Material *Aerogel = new G4Material("Aerogel", 0.2 * g / cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5 * perCent);
    Aerogel->AddMaterial(H2O, 37.4 * perCent);
    Aerogel->AddElement(C, 0.1 * perCent);

    // Shield
    G4Element *W = new G4Element("W", "Tungsten", 74., 183.84 * g / mole);
    G4Material *shieldMat = new G4Material("W", 19.25 * g / cm3, 1);
    shieldMat->AddElement(W, 1.0);

    // Scintillator
    G4Material *scintMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    scintMat->SetName("SCVT");

    // Calorimeter
    G4Material *calorimeterMat = nist->FindOrBuildMaterial("G4_PbWO4");
    calorimeterMat->SetName("PbWO4");

    // Collimator
    G4Material *collimatorMat = nist->FindOrBuildMaterial("G4_Pb");
    collimatorMat->SetName("Pb");
}

void MyDetectorConstruction::ConstructCherenkov(G4LogicalVolume *logicWorld)
{
    G4Box *solidCherenkov = new G4Box("solidCherenkov", 0.4 * m, 0.4 * m, 0.01 * m);
    G4LogicalVolume *logicCherenkov = new G4LogicalVolume(solidCherenkov, G4Material::GetMaterial("Aerogel"), "logicCherenkov");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25 * m), logicCherenkov, "physCherenkov", logicWorld, false, 0, true);
}

void MyDetectorConstruction::ConstructScintillator(G4LogicalVolume *logicWorld)
{
    G4Box *solidScint = new G4Box("solidScint", 5 * cm, 5 * cm, 0.5 * cm);
    G4LogicalVolume *logicScint = new G4LogicalVolume(solidScint, G4Material::GetMaterial("SCVT"), "logicScint");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -20 * cm), logicScint, "physScint", logicWorld, false, 1, true);
}

void MyDetectorConstruction::ConstructCollimator(G4LogicalVolume *logicWorld)
{
    G4Box *solidBlock = new G4Box("CollimatorBlock", 10 * cm, 10 * cm, 5 * cm);
    G4Tubs *solidHole = new G4Tubs("CollimatorHole", 0, 1 * cm, 6 * cm, 0, 360 * deg);
    G4SubtractionSolid *solidCollimator = new G4SubtractionSolid("solidCollimator", solidBlock, solidHole, 0, G4ThreeVector(0, 0, 0));
    G4LogicalVolume *logicCollimator = new G4LogicalVolume(solidCollimator, G4Material::GetMaterial("Pb"), "logicCollimator");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -1.0 * m), logicCollimator, "physCollimator", logicWorld, false, 0, true);
}

void MyDetectorConstruction::ConstructDetector(G4LogicalVolume *logicWorld)
{
    G4Box *solidDetector = new G4Box("solidDetector", 0.4 * m, 0.4 * m, 0.01 * m);
    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, G4Material::GetMaterial("Air"), "logicDetector");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.4 * m), logicDetector, "physDetector", logicWorld, false, 0, true);
}

void MyDetectorConstruction::ConstructCalorimeter(G4LogicalVolume *logicWorld)
{
    G4Box *solidCalorimeter = new G4Box("solidCalorimeter", 0.2 * m, 0.2 * m, 0.2 * m);
    G4LogicalVolume *logicCalorimeter = new G4LogicalVolume(solidCalorimeter, G4Material::GetMaterial("PbWO4"), "logicCalorimeter");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.8 * m), logicCalorimeter, "physCalorimeter", logicWorld, false, 0, true);
}

void MyDetectorConstruction::ConstructShield(G4LogicalVolume *logicWorld, G4String name)
{
    auto mesh = CADMesh::TessellatedMesh::FromSTL("stl/" + name);
    G4VSolid *solidMesh = mesh->GetSolid();
    G4LogicalVolume *logicMesh = new G4LogicalVolume(solidMesh, G4Material::GetMaterial("W"), "logicMesh");
    // new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicMesh, "physMesh", logicWorld, false, 0, true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicMesh, "physMesh", logicWorld, false, 0, false);
}

void MyDetectorConstruction::ConstructControl(G4LogicalVolume* logicWorld) {
    G4Box* solidControl = new G4Box("solidControl", 1.5*cm, 1.5*cm, 1.5*cm);

    G4LogicalVolume* logicControl = new G4LogicalVolume(
        solidControl, 
        G4Material::GetMaterial("W"),
        "logicControl"
    );

    new G4PVPlacement(
        0, 
        G4ThreeVector(0, 0, 0), 
        logicControl, 
        "physControl", 
        logicWorld, 
        false, 
        0, 
        true
    );
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    G4String sdName = "MySD";
    MySensitiveDetector *sensDet = (MySensitiveDetector *)sdManager->FindSensitiveDetector(sdName, false);
    if (!sensDet)
    {
        sensDet = new MySensitiveDetector(sdName);
        sdManager->AddNewDetector(sensDet);
    }
    if (hasCalorimeter)
        SetSensitiveDetector("logicCalorimeter", sensDet);
    if (hasDetector)
        SetSensitiveDetector("logicDetector", sensDet);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();

    G4Box *solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, G4Material::GetMaterial("Air"), "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    if (hasScintillator)
        ConstructScintillator(logicWorld);
    if (hasCollimator)
        ConstructCollimator(logicWorld);
    if (hasCherenkov)
        ConstructCherenkov(logicWorld);
    if (hasShield) {
        if (shieldType == "control")
            ConstructControl(logicWorld);
        else
            ConstructShield(logicWorld, shieldType);
    }
    if (hasDetector)
        ConstructDetector(logicWorld);
    if (hasCalorimeter)
        ConstructCalorimeter(logicWorld);

    return physWorld;
}