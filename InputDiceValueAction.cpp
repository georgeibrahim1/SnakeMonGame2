#include "InputDiceValueAction.h"
#include "Grid.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{
	// no parameters to read from user
}

void InputDiceValueAction::Execute()
{
	int Flag = 0;

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Grid* pGrid = pManager->GetGrid();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if (pGrid->GetEndGame())
	{
		pGrid->PrintErrorMessage("Game has already ended, Click on New Game to start again ........");
		return;
	}
	// -- If not ended, do the following --:

	// 2- Ask the user to enter an a dice value between 1-6
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("please enter a dice value between 1-6 ...");
	int diceNumber = pIn->GetInteger(pOut, Flag); 
	if (diceNumber > 6 || diceNumber < 1)
	{
		pGrid->PrintErrorMessage("Invalid Input");
		return;
	}
	// 3- Get the "current" player from pGrid
	Player* pPlayer = pGrid->GetCurrentPlayer();
	// 4- Move the currentPlayer using function Move of class player
	pPlayer->Move(pGrid, diceNumber);

	// 5- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();

	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

InputDiceValueAction::~InputDiceValueAction()
{
}
