#include "OTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4TwistTrapAlphaSide.hh"
#include "G4TwistedTrap.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"

OTDetectorConstruction::OTDetectorConstruction()
: G4VUserDetectorConstruction()
{
}

OTDetectorConstruction::~OTDetectorConstruction()
{
}

G4VPhysicalVolume* OTDetectorConstruction::Construct()
{
    G4Element* elN;
    G4Element* elO;
    G4Element* elC;
    G4Element* elH;
    G4Element* elAr;
    G4Element* elSi;
    G4Element* elCs;
    G4Element* elI;
//    G4Element* elCs_137;
    G4Element* elAu;

    G4Material* Air;
    G4Material* Vacuum;
    G4Material* PET;
    G4Material* Scint;
    G4Material* Silicon;
    G4Material* CsI;
    G4Material* Cs_tar;
    G4Material* Gold;
	
    //Lab
    G4double labX, labY, labZ;

    //SiCsI detector
    G4double Sisize_1, CsIsize_1, Sisize_2, CsIsize_2, SiThick, CsIThick, Vetosize, VetoThick, Angle1, Angle2, Angle3, Angle4, Angle5, Angle6, Angle7, LCsI_1, LCsI_2, LCsI_3, LCsI_4, LCsI_5, LCsI_6, LCsI_7;
    //const G4String sicsi_PVName;

    //Block neutron detector - jungwoo
    const G4String block_PVName;

    G4double testblock_X, testblock_Y, testblock_Z;
    G4double pad;


  const G4double labTemp = CLHEP::STP_Temperature + 20.*kelvin;

  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*g/mole;
  G4double densityUniverse = 1.e-25*g/CLHEP::cm3;
  G4double tempUniverse= 2.73 *kelvin;
  G4double pressureUniverse = 3.e-18*pascal;

  G4double density_PET = 1.4*g/CLHEP::cm3;

  // Elements
  elN  = new G4Element("Nitrogen", "N",  7,  14.000674*g/mole);
  elO  = new G4Element("Oxygen",   "O",  8,  15.9994*g/mole);
  elC  = new G4Element("Carbon",   "C",  6,  12.011*g/mole);
  elH  = new G4Element("Hydrogen", "H",  1,  1.00794*g/mole);
  elAr = new G4Element("Argon",    "Ar", 18, 39.938*g/mole);
  elSi = new G4Element("Silicon",    "Si", 14, 28.0855*g/mole);
  elCs = new G4Element("Cesium",    "Cs", 55, 132.90543*g/mole);
  elI = new G4Element("Iodine",    "I", 53, 126.90447*g/mole);
  elAu = new G4Element("Gold",   "Au", 79, 196.96656*g/mole); 

  // Materials
  Air = new G4Material("Air", 1.2929e-03*g/CLHEP::cm3, 3, kStateGas, labTemp);
  Air -> AddElement(elN, 75.47/99.95);
  Air -> AddElement(elO, 23.20/99.95);
  Air -> AddElement(elAr, 1.28/99.95);

  // Gold
  Gold = new G4Material("Gold", 19.3*g/cm3, 1, kStateSolid, labTemp);
  Gold -> AddElement(elAu,1);
 
  //Vacuum
  G4double temperature = tempUniverse;
  G4double pressure = pressureUniverse;
  G4double density = densityUniverse;
   
  Vacuum =  new G4Material("Vacuum", density, 2, kStateGas, temperature);
  Vacuum -> AddElement(elO,.3);
  Vacuum -> AddElement(elN,.7);


  PET = new G4Material("PET", density_PET, 3, kStateSolid);
  PET -> AddElement(elC,10);
  PET -> AddElement(elH,8);
  PET -> AddElement(elO,4);

  Scint = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, labTemp);
  Scint -> AddElement(elC, 10);
  Scint -> AddElement(elH, 11);

  //SI
  Silicon = new G4Material("Silicon", 2.33*g/cm3, 1, kStateSolid, labTemp);
  Silicon -> AddElement(elSi, 1);

  //CsI
  CsI = new G4Material("CsI", 4.51*g/cm3, 2, kStateSolid, labTemp);
  CsI -> AddElement(elCs, 1);
  CsI -> AddElement(elI, 1);
 // CsI -> GetIonization() -> SetMeanExcitationEnergy(533.1*eV);


  //Lab
  labX = 1500*CLHEP::mm;
  labY = 1500*CLHEP::mm;
  labZ = 2500*CLHEP::mm;

  
  
  testblock_X = 1500*CLHEP::mm;
  testblock_Y = 1500*CLHEP::mm;
  testblock_Z = 2500*CLHEP::mm;

  pad = 5; // number of pads

/////////////////////////////  Define Parameters ////////////// //////////////////
// Size of Si & CsI Detector - polar angle
  Sisize_1 = 9.00*CLHEP::cm;
  CsIsize_1 = 9.00*CLHEP::cm;
  Vetosize = 9.00*CLHEP::cm;


// Size of Si & CsI Detector - polar angle 
  Sisize_2 = 15*CLHEP::cm;
  CsIsize_2 = 15*CLHEP::cm;

// Thickness of CsI & Si
  SiThick = 100*CLHEP::um;
  CsIThick = 5*CLHEP::cm;
  VetoThick = 300*CLHEP::um;

// Angle
  Angle1 = 25*CLHEP::degree;
  Angle2 = 40*CLHEP::degree;
  Angle3 = 55*CLHEP::degree;
  Angle4 = 70*CLHEP::degree;
  Angle5 = 90*CLHEP::degree;
  Angle6 = 114*CLHEP::degree;
  Angle7 = 138*CLHEP::degree;

// Number of Detectors per unit polar angle
  LCsI_1 = 8;
  LCsI_2 = 12;
  LCsI_3 = 18;
  LCsI_4 = 20;
  LCsI_5 = 15;
  LCsI_6 = 12;
  LCsI_7 = 8;


  G4VSolid* labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
  G4LogicalVolume* labLV = new G4LogicalVolume(labSolid, Vacuum, "labLV");
  G4VPhysicalVolume* labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);

//CsI
  G4Box* TestCsIBlock = new G4Box("TestCsI", CsIsize_1/2, CsIsize_1/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV = new G4LogicalVolume(TestCsIBlock, CsI, "TestCsIBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0*cm,0*cm,(40)*cm+CsIThick+SiThick), "TestCsIBlock_PV", TestCsIBlockLV, labPV, false, 1);
  G4VisAttributes* TestCsIBlockSD = new G4VisAttributes(G4Colour(0.,0.,1));
  TestCsIBlockLV -> SetVisAttributes(TestCsIBlockSD);

//Sillicon
  G4Box* TestSiBlock = new G4Box("TestSi", Sisize_1/2, Sisize_1/2, 100*CLHEP::um/2);
  G4LogicalVolume* TestSiBlockLV = new G4LogicalVolume(TestSiBlock,Silicon, "TestSiBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0*cm,0*cm,(40)*cm),"TestSiBlock_PV", TestSiBlockLV, labPV, false, 11);
  G4VisAttributes* TestSiBlockSD = new G4VisAttributes(G4Colour(1.,0.,0.));
  TestSiBlockLV -> SetVisAttributes(TestSiBlockSD);

//Veto
  G4Box* TestVetoBlock = new G4Box("TestVeto", 9.0*CLHEP::cm/2 , 9.0*CLHEP::cm/2, 300*CLHEP::um/2);
  G4LogicalVolume* TestVetoBlockLV = new G4LogicalVolume(TestVetoBlock, Scint, "TestVetoBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0*cm,0*cm,(40+6)*cm+CsIThick+SiThick+VetoThick), "TestVetoBlock_PV",TestVetoBlockLV, labPV, false,101);
  G4VisAttributes* TestVetoBlockSD = new G4VisAttributes(G4Colour(1.,1.,0.));
  TestVetoBlockLV -> SetVisAttributes(TestVetoBlockSD);


/*
////////////////////////////////////////////////     1st ring    ////////////////////////////////////////////////////////////

  //CsI
  G4Box* TestCsIBlock_1 = new G4Box("TestCsI_1", CsIsize_1/2, CsIsize_1/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_1 = new G4LogicalVolume(TestCsIBlock_1, CsI, "TestCsIBlockLV_1");
  for(G4int i=0; i<LCsI_1; i++)
  {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_1)*i*CLHEP::degree, Angle1,0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40+1)*cm+CsIThick+SiThick).rotateX(Angle1).rotateZ((360/LCsI_1)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_1, labPV, false, i+100);
  }
 
  G4VisAttributes* TestCsIBlockSD = new G4VisAttributes(G4Colour(0.,0.,1.));
  TestCsIBlockLV_1 -> SetVisAttributes(TestCsIBlockSD);


  //Sillicon 
   G4Box* TestSiBlock_1 = new G4Box("TestSi_1", Sisize_1/2, Sisize_1/2, SiThick/2);
   G4LogicalVolume* TestSiBlockLV_1 = new G4LogicalVolume(TestSiBlock_1, Silicon, "TestSiBlockLV_1");
   for(G4int i=0; i<LCsI_1; i++)
   {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_1)*i*CLHEP::degree, Angle1, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle1).rotateZ((360/LCsI_1)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_1, labPV, false, i+150);
   }
  
   G4VisAttributes* TestSiBlockSD = new G4VisAttributes(G4Colour(1.,0.,0.));
   TestSiBlockLV_1 -> SetVisAttributes(TestSiBlockSD);

///////------------------------------   2nd ring --------------------------------------------
  
  //CsI
  G4Box* TestCsIBlock_2 = new G4Box("TestCsI_2", CsIsize_1/2, CsIsize_1/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_2 = new G4LogicalVolume(TestCsIBlock_2, CsI, "TestCsIBlockLV_2");
  for(G4int i=0; i<LCsI_2; i++)
  {
    new G4PVPlacement(new G4RotationMatrix((360/LCsI_2)*i*CLHEP::degree, Angle2, 0),G4ThreeVector(0*cm,0*cm,41*cm+CsIThick/2+SiThick/2).rotateX(Angle2).rotateZ((360/LCsI_2)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_2, labPV, false, i+200);
  }
 
  TestCsIBlockLV_2 -> SetVisAttributes(TestCsIBlockSD);

  //Sillicon 
   G4Box* TestSiBlock_2 = new G4Box("TestSi_2", Sisize_1/2, Sisize_1/2, SiThick/2);
   G4LogicalVolume* TestSiBlockLV_2 = new G4LogicalVolume(TestSiBlock_2, Silicon, "TestSiBlockLV_2");
   for(G4int i=0; i<LCsI_2; i++)
   {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_2)*i*CLHEP::degree, Angle2, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle2).rotateZ((360/LCsI_2)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_2, labPV, false, i+250);
   }
  
   TestSiBlockLV_2 -> SetVisAttributes(TestSiBlockSD);

///////////////////////////////    3rd ring    ////////////////////////////////////////

  //CsI
  G4Box* TestCsIBlock_3 = new G4Box("TestCsI_3", CsIsize_1/2, CsIsize_1/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_3 = new G4LogicalVolume(TestCsIBlock_3, CsI, "TestCsIBlockLV_3");
  for(G4int i=0; i<LCsI_3; i++)
  {
    new G4PVPlacement(new G4RotationMatrix((360/LCsI_3)*i*CLHEP::degree, Angle3, 0),G4ThreeVector(0*cm,0*cm,41*cm+CsIThick/2+SiThick/2).rotateX(Angle3).rotateZ((360/LCsI_3)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_3, labPV, false, i+300);
  }
 
  TestCsIBlockLV_3 -> SetVisAttributes(TestCsIBlockSD);

  //Sillicon 
   G4Box* TestSiBlock_3 = new G4Box("TestSi_3", Sisize_1/2, Sisize_1/2, SiThick/2);
   G4LogicalVolume* TestSiBlockLV_3 = new G4LogicalVolume(TestSiBlock_3, Silicon, "TestSiBlockLV_3");
   for(G4int i=0; i<LCsI_3; i++)
   {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_3)*i*CLHEP::degree, Angle3, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle3).rotateZ((360/LCsI_3)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_3, labPV, false, i+350);
   }
  
   TestSiBlockLV_3 -> SetVisAttributes(TestSiBlockSD);


//////////////////////////////    4th ring    //////////////////////////////////

  //CsI
  G4Box* TestCsIBlock_4 = new G4Box("TestCsI_4", CsIsize_1/2, CsIsize_1/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_4 = new G4LogicalVolume(TestCsIBlock_4, CsI, "TestCsIBlockLV_4");
  for(G4int i=0; i<LCsI_4; i++)
  {
    new G4PVPlacement(new G4RotationMatrix((360/LCsI_4)*i*CLHEP::degree, Angle4, 0),G4ThreeVector(0*cm,0*cm,41*cm+CsIThick/2+SiThick/2).rotateX(Angle4).rotateZ((360/LCsI_4)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_4, labPV, false, i+400);
  }

  TestCsIBlockLV_4 -> SetVisAttributes(TestCsIBlockSD);

  //Sillicon 
  G4Box* TestSiBlock_4 = new G4Box("TestSi_4", Sisize_1/2, Sisize_1/2, SiThick/2);
  G4LogicalVolume* TestSiBlockLV_4 = new G4LogicalVolume(TestSiBlock_4, Silicon, "TestSiBlockLV_4");
  for(G4int i=0; i<LCsI_4; i++)
  {
     new G4PVPlacement(new G4RotationMatrix((360/LCsI_4)*i*CLHEP::degree, Angle4, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle4).rotateZ((360/LCsI_4)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_4, labPV, false, i+450);
   }

  TestSiBlockLV_4 -> SetVisAttributes(TestSiBlockSD);

///////////////////////////    5th ring    /////////////////////////////////////////
  //CsI
  G4Box* TestCsIBlock_5 = new G4Box("TestCsI_5", CsIsize_2/2, CsIsize_2/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_5 = new G4LogicalVolume(TestCsIBlock_5, CsI, "TestCsIBlockLV_5");
  for(G4int i=0; i<LCsI_5; i++)
  {
    new G4PVPlacement(new G4RotationMatrix((360/LCsI_5)*i*CLHEP::degree, Angle5, 0),G4ThreeVector(0*cm,0*cm,41*cm+CsIThick/2+SiThick/2).rotateX(Angle5).rotateZ((360/LCsI_5)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_5, labPV, false, i+500);
  }
 
  TestCsIBlockLV_5 -> SetVisAttributes(TestCsIBlockSD);

  //Sillicon 
   G4Box* TestSiBlock_5 = new G4Box("TestSi_5", Sisize_2/2, Sisize_2/2, SiThick/2);
   G4LogicalVolume* TestSiBlockLV_5 = new G4LogicalVolume(TestSiBlock_5, Silicon, "TestSiBlockLV_5");
   for(G4int i=0; i<LCsI_5; i++)
   {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_5)*i*CLHEP::degree, Angle5, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle5).rotateZ((360/LCsI_5)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_5, labPV, false, i+550);
   }
  
   TestSiBlockLV_5 -> SetVisAttributes(TestSiBlockSD);

////////////////////////////////    6th ring   ////////////////////////////////////////

  //CsI
  G4Box* TestCsIBlock_6 = new G4Box("TestCsI_6", CsIsize_2/2, CsIsize_2/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_6 = new G4LogicalVolume(TestCsIBlock_6, CsI, "TestCsIBlockLV_6");
  for(G4int i=0; i<LCsI_6; i++)
  {
    new G4PVPlacement(new G4RotationMatrix((360/LCsI_6)*i*CLHEP::degree, Angle6, 0),G4ThreeVector(0*cm,0*cm,41*cm+CsIThick/2+SiThick/2).rotateX(Angle6).rotateZ((360/LCsI_6)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_6, labPV, false, i+600);
  }
 
  TestCsIBlockLV_6 -> SetVisAttributes(TestCsIBlockSD);

  //Sillicon 
   G4Box* TestSiBlock_6 = new G4Box("TestSi_6", Sisize_2/2, Sisize_2/2, SiThick/2);
   G4LogicalVolume* TestSiBlockLV_6 = new G4LogicalVolume(TestSiBlock_6, Silicon, "TestSiBlockLV_6");
   for(G4int i=0; i<LCsI_6; i++)
   {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_6)*i*CLHEP::degree, Angle6, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle6).rotateZ((360/LCsI_6)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_6, labPV, false, i+650);
   }
  
   TestSiBlockLV_6 -> SetVisAttributes(TestSiBlockSD);

////////////////////////////////    7th ring   ////////////////////////////////////////

  //CsI
  G4Box* TestCsIBlock_7 = new G4Box("TestCsI_7", CsIsize_2/2, CsIsize_2/2, CsIThick/2);
  G4LogicalVolume* TestCsIBlockLV_7 = new G4LogicalVolume(TestCsIBlock_7, CsI, "TestCsIBlockLV_7");
  for(G4int i=0; i<LCsI_7; i++)
  {
    new G4PVPlacement(new G4RotationMatrix((360/LCsI_7)*i*CLHEP::degree, Angle7, 0),G4ThreeVector(0*cm,0*cm,41*cm+CsIThick/2+SiThick/2).rotateX(Angle7).rotateZ((360/LCsI_7)*i*CLHEP::degree), "TestCsIBlock_PV", TestCsIBlockLV_7, labPV, false, i+700);
  }
 
  TestCsIBlockLV_7 -> SetVisAttributes(TestCsIBlockSD);

  //Sillicon 
   G4Box* TestSiBlock_7 = new G4Box("TestSi_7", Sisize_2/2, Sisize_2/2, SiThick/2);
   G4LogicalVolume* TestSiBlockLV_7 = new G4LogicalVolume(TestSiBlock_7, Silicon, "TestSiBlockLV_7");
   for(G4int i=0; i<LCsI_7; i++)
   {
      new G4PVPlacement(new G4RotationMatrix((360/LCsI_7)*i*CLHEP::degree, Angle7, 0*CLHEP::degree),G4ThreeVector(0*cm,0*cm,(40)*cm).rotateX(Angle7).rotateZ((360/LCsI_7)*i*CLHEP::degree), "TestSiBlock_PV", TestSiBlockLV_7, labPV, false, i+750);
   }
  
   TestSiBlockLV_7 -> SetVisAttributes(TestSiBlockSD);
*/
/*
////////////////////////////////      target      ///////////////////////////////////////////////////////

  G4Box* TargetBlock = new G4Box("Target", 50*CLHEP::mm, 50*CLHEP::mm, 0.0002*CLHEP::mm);
  G4LogicalVolume* TargetBlockLV = new G4LogicalVolume(TargetBlock, Gold, "TargetBlockLV");
  new G4PVPlacement(0, G4ThreeVector(0,0,200*mm), "TargetBlock_PV", TargetBlockLV, labPV, false,0);

  G4VisAttributes* TargetBlockSD = new G4VisAttributes(G4Colour(0.,1.,1.));
  TargetBlockLV -> SetVisAttributes(TargetBlockSD);
*/

  //Det Register
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
/*
  SiCsISD* CsISD = new SiCsISD("/SiCsI/CsISD","CsI");
  sdManager -> AddNewDetector(CsISD);
  TestCsIBlockLV_1 -> SetSensitiveDetector(CsISD);
  TestCsIBlockLV_2 -> SetSensitiveDetector(CsISD);
  TestCsIBlockLV_3 -> SetSensitiveDetector(CsISD);
  TestCsIBlockLV_4 -> SetSensitiveDetector(CsISD);
  TestCsIBlockLV_5 -> SetSensitiveDetector(CsISD);
  TestCsIBlockLV_6 -> SetSensitiveDetector(CsISD);
  TestCsIBlockLV_7 -> SetSensitiveDetector(CsISD);

  SiCsISD* SiSD = new SiCsISD("/SiCsI/SiSD","Si");
  sdManager -> AddNewDetector(SiSD);
  TestSiBlockLV_1 -> SetSensitiveDetector(SiSD);
  TestSiBlockLV_2 -> SetSensitiveDetector(SiSD);
  TestSiBlockLV_3 -> SetSensitiveDetector(SiSD);
  TestSiBlockLV_4 -> SetSensitiveDetector(SiSD);
  TestSiBlockLV_5 -> SetSensitiveDetector(SiSD);
  TestSiBlockLV_6 -> SetSensitiveDetector(SiSD);
  TestSiBlockLV_7 -> SetSensitiveDetector(SiSD);
*/

 // Track_LVSphere -> SetSensitiveDetector(CsISD);

  

  //Define detectors
//  ConstructSiCsI(labPV, sdManager);
//  ConstructBlock(labPV, sdManager);

  return labPV;

}






