#include "Card7.h"
Card7::Card7(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}

Card7::~Card7(void)
{
}


void Card7::Apply(Grid* pGrid, Player* pPlayer)
{


	Card::Apply(pGrid, pPlayer); // call apply of the base class Card

	pGrid->PrintErrorMessage("You get another dice roll! Click anywhere to continue ...");

	// Generate a random number from 1 to 6 
	srand((int)time(NULL)); // time seed
	int diceNumber = 1 + rand() % 6; // from 1 to 6 

	pPlayer->Move(pGrid, diceNumber);

	
}
