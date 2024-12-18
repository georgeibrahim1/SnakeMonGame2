#include "NewGameAction.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}
void NewGameAction::ReadActionParameters()
{
	// This Action doesn't need any parameters
}
 void NewGameAction::Execute()
{
	 Grid* pGrid = pManager->GetGrid();
	 
	 pGrid->ResetGame();

}
NewGameAction::~NewGameAction()
{

}
