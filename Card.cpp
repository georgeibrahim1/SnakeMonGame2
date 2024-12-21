#include "Card.h"


Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	if (cnum > 0 && cnum < 14)
		cardNumber = cnum; // needs validation(done)
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///Done: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(GetPosition(), cardNumber);// Getposition() from GameObject.cpp
	
}

void Card::ReadCardParameters(Grid * pGrid)
{
    // we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

/* Card* Card::GetCard(Grid* pGrid, const CellPosition& pos)
{
	pGrid

}
GameObject* Card::GetCopy()
{
	Card* cardobj = new Card(position);
	
	return cardobj;
}*/
void Card:: SetwalletAmount(int w)
{

}
int Card:: GetwalletAmount()
{
	return 0;
}
void Card::Setcellnum(int w)
{

}
int Card::Getcellnum()
{
	return 0;
}
void Card::GetCopy(Grid* pGrid)
{

}

void Card::Save(ofstream& OutFile, int)
{

}

void Card::Load(ifstream& Infile)
{

}

Card::~Card()
{
}
