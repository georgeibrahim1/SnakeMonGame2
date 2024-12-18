#include "SwitchToDesignMode.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"

SwitchToDesignMode::SwitchToDesignMode(ApplicationManager* pApp) : Action(pApp)
{
    // Initializes the pManager pointer of Action with the passed pointer
}

void SwitchToDesignMode::ReadActionParameters()
{
    // This Action doesn't need any parameters
}

void SwitchToDesignMode::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    pGrid->ResetGame();

    pOut->CreateDesignModeToolBar();

}

SwitchToDesignMode::~SwitchToDesignMode()
{}
