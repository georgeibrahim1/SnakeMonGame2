#include "Card4.h"
#include "Snake.h"
Card4::Card4(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}

Card4::~Card4(void)
{
}


void Card4::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	 // 1- Call Apply() of the base class Card to print the message that you reached this card number

	Card::Apply(pGrid, pPlayer);

	// 2- Move the player forward to the start of the next ladder. (If no ladders ahead, do nothing)
	Snake* pSnake = pGrid->GetNextSnake((this)->GetPosition()); //checks for a ladder ahead (from the position of the card onwards)

	if (pSnake) // if there exists a ladder ahead
	{
		pGrid->UpdatePlayerCell(pPlayer, pSnake->GetPosition());
	}
	else
		pGrid->PrintErrorMessage("No Snakes Ahead, Click to continue ......");
}
