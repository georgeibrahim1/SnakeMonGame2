#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h"
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

	int startcell, endcell; // Cellnumber of the start & end of the snake
	do {
		// Read the startPos parameter
		pOut->PrintMessage("New Snake: Click on its Start Cell ...");
		startPos = pIn->GetCellClicked();

		// Read the endPos parameter
		pOut->PrintMessage("New Snake: Click on its End Cell ...");
		endPos = pIn->GetCellClicked();
		startcell = startPos.GetCellNumFromPosition(startPos); // Cell no. of startPos
		endcell = endPos.GetCellNumFromPosition(endPos); // Cell no. of endPos
		if ((endcell - startcell) % 11 != 0)
		{
			pOut->PrintMessage("Can't draw the snake!");
			this_thread::sleep_for(chrono::seconds(1)); // makes a pause for 1 second

		}
	} while ((endcell - startcell) % 11 != 0); // This validation ensures the start cell & end cell are vertically aligned

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