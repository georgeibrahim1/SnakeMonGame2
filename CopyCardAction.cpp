
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


	//not done yet: if source cell doesn't contain a card, cancel the operation
	pOut->ClearStatusBar();
}
void CopyCardAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Card* pCard = new Card(SourceCell);  	// Create a Card object with the parameters read from the user

	pGrid->SetClipboard(pCard); 	// Copy Card to Clipboard



}