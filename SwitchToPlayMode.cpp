#include "SwitchToPlayMode.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"

SwitchToPlayMode::SwitchToPlayMode(ApplicationManager* pApp) : Action(pApp)
{
    // Initializes the pManager pointer of Action with the passed pointer
}

void SwitchToPlayMode::ReadActionParameters()
{
    // This Action doesn't need any parameters
}

void SwitchToPlayMode::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    pGrid->ResetGame(); 

    pOut->CreatePlayModeToolBar();
    
}

SwitchToPlayMode::~SwitchToPlayMode()
{

}