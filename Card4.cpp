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

	// 2- Move the player forward to the start of the next Snake. (If no snake ahead, do nothing)
	Snake* pSnake = pGrid->GetNextSnake((this)->GetPosition()); //checks for a Snake ahead (from the position of the card onwards)

	if (pSnake) // if there exists a snake ahead
	{
		pGrid->UpdatePlayerCell(pPlayer, pSnake->GetPosition());
		GameObject* existingLadder_or_Snake_or_Card = (pPlayer->GetCell())->GetGameObject();
		if ((pPlayer->GetCell())->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
			existingLadder_or_Snake_or_Card->Apply(pGrid, pPlayer);
		
	}
	else
		pGrid->PrintErrorMessage("No Snakes Ahead, Click to continue ......");
}
