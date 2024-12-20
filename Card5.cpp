#include "Card5.h"

Card5::Card5(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (4 here)
}

Card5::~Card5(void)
{
}


void Card5::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
    int lastRoll = pPlayer->getJustRolledDice();
	pPlayer->Move(pGrid , lastRoll);
	
}

void Card5::Save(ofstream& OutFile, int Obj)
{
    if (Obj == 5)
    {
        OutFile << cardNumber << " " << position.GetCellNum() << endl;
    }
    else
        return;
}

void Card5::Load(ifstream& Infile)
{
    int Cellnum;
    Infile >> Cellnum;
    position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
    position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
}