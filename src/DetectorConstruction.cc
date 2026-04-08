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
    G4Material* water = nist -> FindOrBuildMaterial("G4_WATER");

    // creamos el mundo (universo)
    G4double world_size = 1 * m; //tamaño de cada arista
    G4Box* solidWorld = new G4Box("World",0.5*world_size, 0.5*world_size, 0.5*world_size); // Geometria
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World"); // Material de la geometria construida
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "World", 0, false, 0); // Ubicacion en el espacio

    // creamos un cilindro (Agua del tanque Cherenkov)
    G4double intRadius  = 0. * cm;
    G4double outRadius  = 15. * cm;
    G4double halfHeight = 20. * cm;
    G4double phi0       = 0. * deg;
    G4double phif       = 360. * deg;
    G4Tubs* solidCylider = new G4Tubs("Cylinder", intRadius, outRadius, halfHeight, phi0, phif);
    fLogicCylinder = new G4LogicalVolume(solidCylider, water, "Cylinder");
    new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), fLogicCylinder, "Cylinder", logicWorld, false, 0);
    G4VisAttributes* cylAtt = new G4VisAttributes(G4Colour::Blue()); // color
    cylAtt -> SetForceSolid(true);
    fLogicCylinder -> SetVisAttributes(cylAtt);
    
    // Propiedades opticas del agua del agua (necesaria para la propagacion de fotones en el agua)
    G4MaterialPropertiesTable* WaterProperties = new G4MaterialPropertiesTable();
    G4double WaterPhotonEnergy[] = {
		2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
		2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
		2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
		2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
		3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
		4.002 * eV, 4.136 * eV
	  };

    G4double WaterRefIndex[] = {
		1.3435, 1.344,  1.3445, 1.345,  1.3455, 1.346,  1.3465, 1.347,
		1.3475, 1.348,  1.3485, 1.3492, 1.35,   1.3505, 1.351,  1.3518,
		1.3522, 1.3530, 1.3535, 1.354,  1.3545, 1.355,  1.3555, 1.356,
		1.3568, 1.3572, 1.358,  1.3585, 1.359,  1.3595, 1.36,   1.3608
	  };

    G4int WaterPhotonEntries = sizeof(WaterPhotonEnergy) / sizeof(G4double);
    WaterProperties -> AddProperty("RINDEX", WaterPhotonEnergy, WaterRefIndex, WaterPhotonEntries);

    
    G4double scaleAbsLen = 1.0*m;
    G4double WaterAbsLen[] = {
		3.448*scaleAbsLen,  4.082*scaleAbsLen,  6.329*scaleAbsLen,  9.174*scaleAbsLen,  12.346*scaleAbsLen, 13.889*scaleAbsLen,
		15.152*scaleAbsLen, 17.241*scaleAbsLen, 18.868*scaleAbsLen, 20.000*scaleAbsLen, 26.316*scaleAbsLen, 35.714*scaleAbsLen,
		45.455*scaleAbsLen, 47.619*scaleAbsLen, 52.632*scaleAbsLen, 52.632*scaleAbsLen, 55.556*scaleAbsLen, 52.632*scaleAbsLen,
		52.632*scaleAbsLen, 47.619*scaleAbsLen, 45.455*scaleAbsLen, 41.667*scaleAbsLen, 37.037*scaleAbsLen, 33.333*scaleAbsLen,
		30.000*scaleAbsLen, 28.500*scaleAbsLen, 27.000*scaleAbsLen, 24.500*scaleAbsLen, 22.000*scaleAbsLen, 19.500*scaleAbsLen,
		17.500*scaleAbsLen, 14.500*scaleAbsLen
    };
    WaterProperties -> AddProperty("ABSLENGTH", WaterPhotonEnergy, WaterAbsLen, WaterPhotonEntries);
    
    G4double water2PhotonEnergyMie[] = {
		1.56962 * eV, 1.58974 * eV, 1.61039 * eV, 1.63157 * eV, 1.65333 * eV,
		1.67567 * eV, 1.69863 * eV, 1.72222 * eV, 1.74647 * eV, 1.77142 * eV,
		1.7971 * eV,  1.82352 * eV, 1.85074 * eV, 1.87878 * eV, 1.90769 * eV,
		1.93749 * eV, 1.96825 * eV, 1.99999 * eV, 2.03278 * eV, 2.06666 * eV,
		2.10169 * eV, 2.13793 * eV, 2.17543 * eV, 2.21428 * eV, 2.25454 * eV,
		2.29629 * eV, 2.33962 * eV, 2.38461 * eV, 2.43137 * eV, 2.47999 * eV,
		2.53061 * eV, 2.58333 * eV, 2.63829 * eV, 2.69565 * eV, 2.75555 * eV,
		2.81817 * eV, 2.88371 * eV, 2.95237 * eV, 3.02438 * eV, 3.09999 * eV,
		3.17948 * eV, 3.26315 * eV, 3.35134 * eV, 3.44444 * eV, 3.54285 * eV,
		3.64705 * eV, 3.75757 * eV, 3.87499 * eV, 3.99999 * eV, 4.13332 * eV,
		4.27585 * eV, 4.42856 * eV, 4.59258 * eV, 4.76922 * eV, 4.95999 * eV,
		5.16665 * eV, 5.39129 * eV, 5.63635 * eV, 5.90475 * eV, 6.19998 * eV	
	  };

    G4double water2Mie[] = {
		167024.4 * m, 158726.7 * m, 150742 * m,   143062.5 * m, 135680.2 * m,
		128587.4 * m, 121776.3 * m, 115239.5 * m, 108969.5 * m, 102958.8 * m,
		97200.35 * m, 91686.86 * m, 86411.33 * m, 81366.79 * m, 76546.42 * m,
		71943.46 * m, 67551.29 * m, 63363.36 * m, 59373.25 * m, 55574.61 * m,
		51961.24 * m, 48527.00 * m, 45265.87 * m, 42171.94 * m, 39239.39 * m,
		36462.50 * m, 33835.68 * m, 31353.41 * m, 29010.30 * m, 26801.03 * m,
		24720.42 * m, 22763.36 * m, 20924.88 * m, 19200.07 * m, 17584.16 * m,
		16072.45 * m, 14660.38 * m, 13343.46 * m, 12117.33 * m, 10977.70 * m,
		9920.416 * m, 8941.407 * m, 8036.711 * m, 7202.470 * m, 6434.927 * m,
		5730.429 * m, 5085.425 * m, 4496.467 * m, 3960.210 * m, 3473.413 * m,
		3032.937 * m, 2635.746 * m, 2278.907 * m, 1959.588 * m, 1675.064 * m,
		1422.710 * m, 1200.004 * m, 1004.528 * m, 833.9666 * m, 686.1063 * m
	  };
    G4int Water2PhotonMieEntries = sizeof(water2PhotonEnergyMie) / sizeof(G4double);
    WaterProperties -> AddProperty("MIEHG", water2PhotonEnergyMie, water2Mie, Water2PhotonMieEntries);

    //G4double water2MieConst[3] = { 0.99, 0.99, 0.8 };
    WaterProperties -> AddConstProperty("MIEHG_FORWARD", 0.99);
    WaterProperties -> AddConstProperty("MIEHG_BACKWARD", 0.99);
    WaterProperties -> AddConstProperty("MIEHG_FORWARD_RATIO", 0.8);
    
    water -> SetMaterialPropertiesTable(WaterProperties);

    
    


    return physWorld; // retornamos el muno (donde esta todo lo construido)
}