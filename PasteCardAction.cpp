#include "PasteCardAction.h"
#include "Input.h"
#include "Output.h"
//#include "Card.h"
#include "CardOne.h"
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


	//not done yet: if source cell doesn't contain a card, cancel the operation
	pOut->ClearStatusBar();
}
void PasteCardAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	 PasteCardAction :: ReadActionParameters();
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Card* pCard = NULL;
	if (!(pGrid->HasObject(DestinationCell))) // this should be a function because it's also used in addcardaction
	{
		pCard = pGrid->GetClipboard();
		int CardNumber = pCard->GetCardNumber();
		switch (CardNumber)
		{
		case 1:
			pCard = new CardOne(DestinationCell);
			break;

			// A- Add the remaining cases

		}
		bool added = pGrid->AddObjectToCell(pCard); // to here

	}
	else
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	



}
