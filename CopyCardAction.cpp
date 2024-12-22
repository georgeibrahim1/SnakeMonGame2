
#include "CopyCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"

CopyCardAction::CopyCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}
CopyCardAction::~CopyCardAction()
{
}
void CopyCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the source cell parameter
	pOut->PrintMessage("Copy Card: Click on the source cell ...");
	SourceCell = pIn->GetCellClicked();

	pOut->ClearStatusBar();
}
void CopyCardAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	if (!(SourceCell.IsValidCell())) // to check if the cell clicked is valid
	{
		pGrid->PrintErrorMessage("You didn't click anywhere on the grid! Click to continue....");
		
	}


	else if (pGrid->GetObj(SourceCell)) // Check if the cell has an object
	{
		if (dynamic_cast<Card*>(pGrid->GetObj(SourceCell)))
		{
			pGrid->Copy(SourceCell, pGrid);
			pGrid->PrintErrorMessage("Card  Copied To Clipboard,  Click to continue ...");
		}
		else
			pGrid->PrintErrorMessage("Error: Cell doesn't have a card ! Click to continue ...");


	}
	else 
		pGrid->PrintErrorMessage("Error: Cell doesn't have a card ! Click to continue ...");




}