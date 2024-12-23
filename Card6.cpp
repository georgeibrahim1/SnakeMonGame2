#include "Card6.h"

Card6::Card6(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (4 here)
}

Card6::~Card6(void)
{
}

void Card6::GetCopy(Grid* pGrid)
{
    Card* c;
    c = new Card6(this->GetPosition());
    c->SetCardNumber(6);
    pGrid->SetClipboard(c);

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
    GameObject* pGameObject = (pPlayer->GetCell())->GetGameObject();

    if (pGameObject != nullptr)
    {
       pGameObject->Apply(pGrid, pPlayer);
    }
    pGrid->PrintErrorMessage("Card6: You moved backward by " + to_string(lastRoll) + " steps! Click anywhere to continue...");
}

void Card6::Save(ofstream& OutFile, int Obj)
{
    if (Obj == 6)
    {
        OutFile << cardNumber << " " << position.GetCellNum() << endl;
    }
    else
        return;
}

void Card6::Load(ifstream& Infile)
{
    int Cellnum;
    Infile >> Cellnum;
    position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
    position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
}
