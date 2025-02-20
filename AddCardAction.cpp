#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "Card2.h"
#include "Card3.h"
#include "Card4.h"
#include "Card9.h"
#include "Card5.h"
#include "Card6.h"
#include "Card7.h"
#include "Card8.h"


#include "Card10.h"
#include "Card11.h"
#include "Card12.h"
#include "Card13.h"
#include <iostream>
#include <chrono>
#include <thread>


AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///Done: Implement this function as mentioned in the guideline steps (numbered below) below
	int Flag = 0;// Used in get integer
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Card: Type in card number ...");
	cardNumber = pIn->GetInteger(pOut,Flag);
	while (Flag != 0 || cardNumber < 1 || cardNumber > 13)//Must be between 1 & 13
	{
		pOut->PrintMessage("Invalid Input!");
		this_thread::sleep_for(chrono::seconds(1));
		pOut->PrintMessage("Please type in a valid Card Number ...");
		cardNumber = pIn->GetInteger(pOut, Flag);
	}
	pOut->PrintMessage("New Card: Click on its Cell ...");
	cardPosition = pIn->GetCellClicked();
	pOut->ClearStatusBar();

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	
	// 2- Read the "cardNumber" parameter and set its data member
	
	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
}

void AddCardAction::Execute() 
{

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	
	// 2- Switch case on cardNumber data member and create the appropriate card object type

	AddCardAction :: ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (!(cardPosition.IsValidCell())) // to check if the cell clicked is valid
	{
		pGrid->PrintErrorMessage("You didn't click anywhere on the grid! Click to continue....");
		return;
	}
	if (pGrid->HasObject(cardPosition))
	{
		pGrid->PrintErrorMessage("This cell has another object!");
			return;
	}
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;
	case 2:
		pCard = new Card2(cardPosition);
		break;
	case 3:
		pCard = new Card3(cardPosition);
		break;
	case 4:
		pCard = new Card4(cardPosition);
		break;
	case 5 :
		pCard = new Card5(cardPosition);
		break;
	case 6:
		pCard = new Card6(cardPosition);
		break;
	case 7:
		pCard = new Card7(cardPosition);
		break;
	case 8:
		pCard = new Card8(cardPosition);
		break;
	case 9:
		pCard = new Card9(cardPosition);
		break;
	case 10:
		pCard = new Card10(cardPosition);
		break;
	case 11:
		pCard = new Card11(cardPosition);
		break;
	case 12:
		pCard = new Card12(cardPosition);
		break;
	case 13:
		pCard = new Card13(cardPosition);
		break;
		// A- Add the remaining cases

	}
	
	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type

		// C- Add the card object to the GameObject of its Cell:

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		Grid* pGrid = pManager->GetGrid();
		pCard->ReadCardParameters(pGrid);
		bool added = pGrid->AddObjectToCell(pCard);
		if (!added)
		{
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}

	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
