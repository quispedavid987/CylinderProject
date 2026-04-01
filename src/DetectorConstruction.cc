#include "DetectorConstruction.h"
#include "G4NistManager.hh" // llamar a los materiales
#include "G4Tubs.hh" // llamar a las formas tubulares
#include "G4Box.hh" // formas de cajas
#include "G4Ellipsoid.hh" // forma elipsoise
#include "G4LogicalVolume.hh" // declarar volumenes
#include "G4PVPlacement.hh" // lugares simulacion
#include "G4SystemOfUnits.hh" // unidades
#include "G4VisAttributes.hh" // atributos de visualizacion
#include "G4Colour.hh" // Colores

MyDetectorconstruction::MyDetectorconstruction():G4VUserDetectorConstruction(){}
MyDetectorconstruction::~MyDetectorconstruction(){}

G4VPhysicalVolume* MyDetectorconstruction::Construct()
{
    // declaramos los materiales a usar
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist -> FindOrBuildMaterial("G4_AIR");
    G4Material* lead = nist -> FindOrBuildMaterial("G4_WATER");

    // creamos el mundo (universo)
    G4double world_size = 1 * m; //tamaño de cada arista
    G4Box* solidWorld = new G4Box("World",0.5*world_size, 0.5*world_size, 0.5*world_size); // Geometria
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World"); // Material de la geometria construida
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "World", 0, false, 0); // Ubicacion en el espacio

    // creamos un cilindro (dentro del universo)
    G4double intRadius  = 0. * cm;
    G4double outRadius  = 15. * cm;
    G4double halfHeight = 20. * cm;
    G4double phi0       = 0. * deg;
    G4double phif       = 360. * deg;
    G4Tubs* solidCylider = new G4Tubs("Cylinder", intRadius, outRadius, halfHeight, phi0, phif);
    fLogicCylinder = new G4LogicalVolume(solidCylider, lead, "Cylinder");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), fLogicCylinder, "Cylinder", logicWorld, false, 0);
    G4VisAttributes* cylAtt = new G4VisAttributes(G4Colour::Blue()); // color
    cylAtt -> SetForceSolid(true);
    fLogicCylinder -> SetVisAttributes(cylAtt);

    /*=============================

    G4double semiXaxes = 5. * cm;
    G4double semiYaxes = 8. * cm;
    G4double semiZaxes = 3. * cm;
    G4double pzBottomCut = 0;
    G4double pzTopCut = 0;
    G4Ellipsoid* solidEllipsoid = new G4Ellipsoid("Ellipsoid", semiXaxes, semiYaxes, semiZaxes, pzBottomCut, pzTopCut);
    fLogicEllipsoid = new G4LogicalVolume(solidEllipsoid, lead, "Ellipsoid");
    new G4PVPlacement(0, G4ThreeVector(20., 20., 20.)*cm, fLogicEllipsoid, "Ellipsoid", logicWorld, false, 0);
    G4VisAttributes* ellipAtt = new G4VisAttributes(G4Colour::Red());
    //ellipAtt -> SetForceSolid(true);
    fLogicEllipsoid -> SetVisAttributes(ellipAtt);

    ===============================*/

    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    G4double energy[] = {2.0*eV, 3.0*eV, 3.0*eV};
    G4double rindex[] = {1.33, 1.33, 1.33};

    mpt -> AddProperty("RINDEX", energy, rindex, 3);
    lead -> SetMaterialPropertiesTable(mpt);

    return physWorld; // retornamos el muno (donde esta todo lo construido)
}