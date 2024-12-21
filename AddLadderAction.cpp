#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "GameObject.h"
#include "Card.h"
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
	
		// Read the startPos parameter
		pOut->PrintMessage("New Ladder: Click on its Start Cell (bottom of ladder) ...");
		startPos = pIn->GetCellClicked();
		/*if (!startPos.IsValidCell())
		{
			pOut->PrintMessage("Invalid Cell");
			this_thread::sleep_for(chrono::seconds(1)); // makes a pause for 1 second
			return;
		}*/
		// Read the endPos parameter
		pOut->PrintMessage("New Ladder: Click on its End Cell (top of ladder) ...");
		endPos = pIn->GetCellClicked();
		/*startcell = startPos.GetCellNumFromPosition(startPos); // Cell no. of startPos
		endcell = endPos.GetCellNumFromPosition(endPos); // Cell no. of endPos
		if (startcell>endcell)
		{
			pOut->PrintMessage("End Cell can't be smaller than Start Cell!");
			return;
		}
		if((endcell - startcell) % 11 != 0)
		{
			pOut->PrintMessage("Start Cell & End Cell must be in the same column!");
			return;
		}

	 // This validation ensures the start cell & end cell are vertically aligned*/
		

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
	if (!startPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Invalid Cell");
		this_thread::sleep_for(chrono::seconds(1)); // makes a pause for 1 second
		return;
	}
	int startcell = startPos.GetCellNumFromPosition(startPos); // Cell no. of startPos
	int endcell = endPos.GetCellNumFromPosition(endPos); // Cell no. of endPos
	if (startcell > endcell && (endcell - startcell) % 11 == 0)// Added 2nd condition cuz without it the "Same Column" Error won't be executed if startcell is greater than endcell (otherwise no need for this validation)
	{
		pGrid->PrintErrorMessage("End Cell can't be smaller than Start Cell!");
		return;
	}
	if ((endcell - startcell) % 11 != 0)
	{
		pGrid->PrintErrorMessage("Start Cell & End Cell must be in the same column!");
		return;
	}
	/*GameObject* cardobject = cardobject->GetCopy();
	Card* Cardobject = dynamic_cast<Card*>(cardobject);*/
	GameObject* isCard = pGrid->GetObj(endPos);
	Card* HasCard = dynamic_cast<Card*>(isCard);
	if (pGrid->HasObject(endPos) && !HasCard)
	{
		pGrid->PrintErrorMessage("End Cell cannot be the start of another ladder or snake");//This error occurs when Top of New Ladder is with Bottom of Old Ladder or with Head of Snake
		return;
	}

	GameObject* C = pLadder;// A pointer of type gameobject to send it to overlap function
	
	if (pGrid->IsOverlapping(C))
	{
		pGrid->PrintErrorMessage("Overlapping occured!");
		return;
	}
	if (pGrid->Check_snakeendcell_ladderendcell_loop(C))
	{
		pGrid->PrintErrorMessage("Start Cell of a ladder cannot be the End Cell of a snake");
		return;
	}
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
