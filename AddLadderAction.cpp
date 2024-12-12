#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include <iostream>
#include <chrono>
#include <thread>

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	int startcell, endcell; // Cellnumber of the start & end of the ladder
	do {
		// Read the startPos parameter
		pOut->PrintMessage("New Ladder: Click on its Start Cell (bottom of ladder) ...");
		startPos = pIn->GetCellClicked();

		// Read the endPos parameter
		pOut->PrintMessage("New Ladder: Click on its End Cell (top of ladder) ...");
		endPos = pIn->GetCellClicked();
		startcell = startPos.GetCellNumFromPosition(startPos); // Cell no. of startPos
		endcell = endPos.GetCellNumFromPosition(endPos); // Cell no. of endPos
		if((endcell - startcell) % 11 != 0 || (startcell>endcell))
		{
			pOut->PrintMessage("Can't draw the ladder!");
			this_thread::sleep_for(chrono::seconds(1)); // makes a pause for 1 second

		}
	} while ((endcell - startcell) % 11 != 0 || (startcell > endcell)); // This validation ensures the start cell & end cell are vertically aligned
		

	///Done: Make the needed validations on the read parameters

	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
