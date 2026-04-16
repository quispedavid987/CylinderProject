#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH 1

// Librerias de G4
//  Plantillas de Geant4 para construccion
#include "G4VUserDetectorConstruction.hh"
//  Plantilla de tipo de datos G4int, G4double, etc
#include "globals.hh"

// Avisamos al compilador que classes vamos a declarar
class G4VPhysicalVolume;
class G4LogicalVolume;

// MyDetectorConstruction hereda de G4VUserDetectorConstruction
class MyDetectorconstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorconstruction();
    virtual ~MyDetectorconstruction();

    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume* fLogicCylinder;
    //G4LogicalVolume*  fLogicEllipsoid;
    G4LogicalVolume* fLogicalFiber; 
};



#endif