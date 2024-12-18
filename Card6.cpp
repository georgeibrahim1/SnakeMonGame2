#include "Card6.h"

Card6::Card6(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (4 here)
}

Card6::~Card6(void)
{
}


void Card6::Apply(Grid* pGrid, Player* pPlayer)
{

    Card::Apply(pGrid, pPlayer);
    int lastRoll = pPlayer->getJustRolledDice();
    CellPosition currentPosition = pPlayer->GetCell()->GetCellPosition();
    currentPosition.AddCellNum(-lastRoll);

    if (currentPosition.GetCellNum() < 1)
    {
        currentPosition.SetVCell(8); 
        currentPosition.SetHCell(0); 
    }
    pGrid->UpdatePlayerCell(pPlayer, currentPosition);
    GameObject* pGameObject = pGrid->GetObj(currentPosition);

    if (pGameObject != nullptr)
    {
       pGameObject->Apply(pGrid, pPlayer);
    }
    pGrid->PrintErrorMessage("Card6: You moved backward by " + to_string(lastRoll) + " steps! Click anywhere to continue...");
}