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



}
