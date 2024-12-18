#include "DeleteObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "GameObject.h"

DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}
DeleteObjectAction::~DeleteObjectAction()
{

}
void DeleteObjectAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("Delete Object: Click on an Object...");
	Pos = pIn->GetCellClicked();



	// Clear messages
	pOut->ClearStatusBar();
}
void DeleteObjectAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	if (!(Pos.IsValidCell())) // to check if the cell clicked is valid
	{
		pGrid->PrintErrorMessage("You didn't click anywhere on the grid! Click to continue....");
	}


	else if (pGrid->HasObject(Pos))
	{
		// remove the GameObject of its Cell:
		pGrid->RemoveObjectFromCell(Pos);
	}
	else
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error:There is no object in cell ! Click to continue ...");

}