#include "PasteCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"
PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}
PasteCardAction::~PasteCardAction()
{
}
void PasteCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the source cell parameter
	pOut->PrintMessage("Paste Card: Click on the Destination cell ...");
	DestinationCell = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}
void PasteCardAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	PasteCardAction::ReadActionParameters();
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	if (!(DestinationCell.IsValidCell())) // to check if the cell clicked is valid
	{
		pGrid->PrintErrorMessage("You didn't click anywhere on the grid! Click to continue....");
	}
	else
	{
		Card* pCard = NULL;
		bool added = 0; // to check if the card was added
		pCard = pGrid->GetClipboard(); // gets the Card pointer from clipboard
		if (pCard)
		{
			pCard->SetPosition(DestinationCell);
			added = pGrid->AddObjectToCell(pCard); // pastes the card to the desired cell
			if (added == 0) // Fails to add because there is an object in that cell
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		else
			pGrid->PrintErrorMessage("Error: Clipboard is empty ! Click to continue ...");


	}



}
