#include "Card7.h"
Card7::Card7(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}

Card7::~Card7(void)
{
}

void Card7::GetCopy(Grid* pGrid)
{
	Card* c;
	c = new Card7(this->GetPosition());
	c->SetCardNumber(7);
	pGrid->SetClipboard(c);

}

void Card7::Apply(Grid* pGrid, Player* pPlayer)
{


	Card::Apply(pGrid, pPlayer); // call apply of the base class Card

	pGrid->PrintErrorMessage("You get another dice roll! Click anywhere to continue ...");

	// Generate a random number from 1 to 6 
	srand((int)time(NULL)); // time seed
	int diceNumber = 1 + rand() % 6; // from 1 to 6 
	pPlayer->SetAnotherRoll(1); // indicates that this is a second roll, turncount won't increase again
	pPlayer->Move(pGrid, diceNumber); // moves the pkayer again with the new roll
	
}

void Card7::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 7)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
	else
		return;
}

void Card7::Load(ifstream& Infile)
{
	int Cellnum;
	Infile >> Cellnum;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
}