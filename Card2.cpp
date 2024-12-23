#include "Card2.h"
#include <iostream>
#include <chrono>
#include <thread>
Card2::Card2(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
	walletAmount = 0;
}

Card2::~Card2(void)
{
}

void Card2::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardTwo: Enter its wallet amount to increase player's Total Wallet ...");
	int Flag = 0;
	walletAmount = pIn->GetInteger(pOut, Flag);
	while (Flag != 0 || walletAmount < 0)
	{
		pOut->PrintMessage("Invalid Input!");
		this_thread::sleep_for(chrono::seconds(1));
		pOut->PrintMessage("Please type in a valid Number ...");
		walletAmount = pIn->GetInteger(pOut, Flag);
	}
	pOut->ClearStatusBar();
}

void Card2::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pPlayer->SetWallet(pPlayer->GetWallet() + walletAmount);// Set the wallet with updated coins

}
void Card2::SetwalletAmount(int w)
{
	walletAmount = w;
}
int Card2::GetwalletAmount()
{
	return walletAmount;
}
void Card2::GetCopy(Grid* pGrid)
{
	Card* c;
	c = new Card2(this->GetPosition());
	c->SetCardNumber(2);
	c->SetwalletAmount(this->GetwalletAmount());
	pGrid->SetClipboard(c);

}

void Card2::Load(ifstream& Infile)
{
	int Cellnum, WA;
	Infile >> Cellnum >> WA;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
	this->walletAmount = WA;
}

void Card2::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 2)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << walletAmount << endl;
	}
	else
		return;
}