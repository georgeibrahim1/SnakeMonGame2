#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h"
#include "Card.h"
#include <iostream>
#include <chrono>
#include <thread>

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}
void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	/*int startcell, endcell; // Cellnumber of the start & end of the snake
	do {
		// Read the startPos parameter
		pOut->PrintMessage("New Snake: Click on its Start Cell (top of snake) ...");
		startPos = pIn->GetCellClicked();

		// Read the endPos parameter
		pOut->PrintMessage("New Snake: Click on its End Cell (bottom of snake) ...");
		endPos = pIn->GetCellClicked();
		startcell = startPos.GetCellNumFromPosition(startPos); // Cell no. of startPos
		endcell = endPos.GetCellNumFromPosition(endPos); // Cell no. of endPos
		if ((endcell - startcell) % 11 != 0 || (endcell > startcell))
		{
			pOut->PrintMessage("Can't draw the snake!");
			this_thread::sleep_for(chrono::seconds(1)); // makes a pause for 1 second

		}
	} while ((endcell - startcell) % 11 != 0 || (endcell > startcell)); // This validation ensures the start cell & end cell are vertically aligned*/
	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell (top of snake) ...");
	startPos = pIn->GetCellClicked();
	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell (bottom of snake) ...");
	endPos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}
// Execute the action
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Snake object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	if (!startPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Invalid Cell");
		this_thread::sleep_for(chrono::seconds(1)); // makes a pause for 1 second
		return;
	}
	int startcell = startPos.GetCellNumFromPosition(startPos); // Cell no. of startPos
	int endcell = endPos.GetCellNumFromPosition(endPos); // Cell no. of endPos
	if (endcell > startcell && ((startcell - endcell) % 11 == 0)) // Added 2nd condition cuz without it the "Same Column" Error won't be executed if endcell is greater than startcell (otherwise no need for this validation)
	{
		pGrid->PrintErrorMessage("Start Cell can't be smaller than End Cell!");
		return;
	}
	if ((startcell - endcell) % 11 != 0)
	{
		pGrid->PrintErrorMessage("Start Cell & End Cell must be in the same column!");
		return;
	}
	GameObject* isCard = pGrid->GetObj(endPos);
	Card* HasCard = dynamic_cast<Card*>(isCard);
	if (pGrid->HasObject(endPos) && !HasCard)
	{
		pGrid->PrintErrorMessage("End Cell cannot be the start of another ladder or snake");//This error occurs when Tail of New Snake is with Head of Old Snake or Bottom of Ladder
		return;
	}

	GameObject* C = pSnake;

	if (pGrid->IsOverlapping(C))
	{
		pGrid->PrintErrorMessage("Overlapping occured!");
		return;
	}
	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction

}