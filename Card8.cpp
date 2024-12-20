#include "Card8.h"
Card8::Card8(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
}

Card8::~Card8(void)
{
}


void Card8::Apply(Grid* pGrid, Player* pPlayer)
{


	Card::Apply(pGrid, pPlayer); // call apply of the base class Card

	pPlayer->SetToSkip(1); // Indicating that the player will skip next turn
	pGrid->PrintErrorMessage("You will skip next turn. Click to continue ......");

}

void Card8::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 8)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
	else
		return;
}

void Card8::Load(ifstream& Infile)
{
	int Cellnum;
	Infile >> Cellnum;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
}