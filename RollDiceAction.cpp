#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"
#include "Output.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if (pGrid->GetEndGame())
	{
		pGrid->PrintErrorMessage("Game has already ended, Click on New Game to start again ........");
		return;
	}
	// -- If not ended, do the following --:

	// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed
	// 3- Get the "current" player from pGrid
	Player* pPlayer = pGrid->GetCurrentPlayer();
	CellPosition OldPosition = pPlayer->GetCell()->GetCellPosition();
	
	// 4- Move the currentPlayer using function Move of class player
	pPlayer->Move(pGrid, diceNumber);
	
	CellPosition NewPosition = pPlayer->GetCell()->GetCellPosition();

	// 5- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();

	if (OldPosition.GetCellNum() != NewPosition.GetCellNum())
	{
		pGrid->PrintErrorMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " rolled " + to_string(diceNumber) + " || " + "Moved from Cell " + to_string(OldPosition.GetCellNum()) + " to Cell " + to_string(NewPosition.GetCellNum()) + " , Click anywhere to continue...");
	}

	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

RollDiceAction::~RollDiceAction()
{
}
