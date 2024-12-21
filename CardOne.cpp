#include "CardOne.h"
#include <iostream>
#include <chrono>
#include <thread>
CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	walletAmount = 0;
}

CardOne::~CardOne(void)
{
}
void CardOne::SetwalletAmount(int w)
{
	walletAmount = w;
}
int CardOne::GetwalletAmount()
{
	return walletAmount;
}
void CardOne::GetCopy(Grid* pGrid)
{
	Card* c;
	c = new CardOne(this->GetPosition());
	c->SetCardNumber(1);
	c->SetwalletAmount(this->GetwalletAmount());
	pGrid->SetClipboard(c);

}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///DONE: Implement this function as mentioned in the guideline steps (numbered below) below

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardOne: Enter its wallet amount to decrease player's Total Wallet ...");
	int Flag=0;
	walletAmount = pIn->GetInteger(pOut, Flag);
	while (Flag != 0 || walletAmount < 0)
	{
		pOut->PrintMessage("Invalid Input!");
		this_thread::sleep_for(chrono::seconds(1));
		pOut->PrintMessage("Please type in a valid Number ...");
		walletAmount = pIn->GetInteger(pOut, Flag);
	}
	pOut->ClearStatusBar();

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	

	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar

}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	
	Card::Apply(pGrid, pPlayer);
	pPlayer->SetWallet(pPlayer->GetWallet() - walletAmount);
	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number

	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne

}

void CardOne::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 1)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << walletAmount << endl;
	}
	else
		return;
}

void CardOne::Load(ifstream& Infile)
{
	int Cellnum , WA;
	Infile >> Cellnum >> WA;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
	this->walletAmount = WA;

}