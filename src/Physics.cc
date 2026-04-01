#include "Physics.h"


MyPhysicsList::MyPhysicsList()
{
RegisterPhysics (new G4EmStandardPhysics());

// IMPLEMENTANDO LA FISICA OPTICA
G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
RegisterPhysics (opticalPhysics);

opticalPhysics -> SetVerboseLevel(1);



 
}

MyPhysicsList::~MyPhysicsList() {}