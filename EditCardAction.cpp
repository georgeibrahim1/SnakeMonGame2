#include "EditCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"



EditCardAction::EditCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

EditCardAction::~EditCardAction()
{
}

void EditCardAction::ReadActionParameters()
{
	int Flag = 0;
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	pOut->PrintMessage("Edit Card: Click on its Cell ...");
	cardPosition = pIn->GetCellClicked();
	pOut->ClearStatusBar();

}

void EditCardAction::Execute()
{


	

	EditCardAction::ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (!(cardPosition.IsValidCell())) // to check if the cell clicked is valid
	{
		pGrid->PrintErrorMessage("you didn't click anywhere on the grid! Click to continue....");
		return;
	}

	Card* pCard = NULL; // will point to the card object type

	if (pCard)
	{
		

	}

}
