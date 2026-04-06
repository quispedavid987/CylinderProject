#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.h"
#include "Physics.h"
#include "PrimaryGeneratorAction.h"

// incluimos lo trabajado

int main(G4int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();
    // Vamos poniendo lo que vamos construyendo
    runManager -> SetUserInitialization(new MyDetectorconstruction()); // llamamos la detector construido
    runManager -> SetUserInitialization(new MyPhysicsList());
    runManager -> SetUserInitialization(new MyActionInitialization());
    // 

    runManager -> Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    G4UImanager *UIManager = G4UImanager::GetUIpointer();

    G4VisManager *visManager = new G4VisExecutive();
    visManager -> Initialize();

    // vamos poniendo los comandos inciales
    UIManager->ApplyCommand("/vis/open OGL"); // Abre la imagen del detector
        UIManager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1.7 1.2");
    UIManager->ApplyCommand("/vis/ogl/set/displayListLimit 50000");

    UIManager->ApplyCommand("/vis/drawVolume");
    UIManager->ApplyCommand("/vis/scene/add/axes 0 0 0 50 cm");
    UIManager->ApplyCommand("/vis/viewer/set/autorefresh true");
    UIManager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UIManager->ApplyCommand("/vis/scene/endOfEventAction accumulate 300");

    UIManager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
    UIManager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e- blue");
    UIManager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set mu- red");
    UIManager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set mu+ red");

    UIManager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set opticalphoton green");
    //

    ui -> SessionStart();

    delete visManager;
    delete runManager;
    G4cout << "========== Simulacion completa ===========" << G4endl;
    return 0;
}