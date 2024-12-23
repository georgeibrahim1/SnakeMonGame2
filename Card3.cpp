#include "Card3.h"
#include "Ladder.h"
Card3::Card3(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

Card3::~Card3(void)
{
}

void Card3::GetCopy(Grid* pGrid)
{
	Card* c;
	c = new Card3(this->GetPosition()); 
	c->SetCardNumber(3);
	pGrid->SetClipboard(c); 

}


void Card3::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	 // 1- Call Apply() of the base class Card to print the message that you reached this card number

	Card::Apply(pGrid, pPlayer);

	// 2- Move the player forward to the start of the next ladder. (If no ladders ahead, do nothing)
	Ladder* pLadder = pGrid->GetNextLadder((this)->GetPosition()); //checks for a ladder ahead (from the position of the card onwards)

	if (pLadder) // if there exists a ladder ahead
	{
		pGrid->UpdatePlayerCell(pPlayer, pLadder->GetPosition());
		GameObject* existingLadder_or_Snake_or_Card = (pPlayer->GetCell())->GetGameObject();
		if ((pPlayer->GetCell())->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
			existingLadder_or_Snake_or_Card->Apply(pGrid, pPlayer);
	}
	else
		pGrid->PrintErrorMessage("No ladders Ahead, Click to continue ......");
}

void Card3::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 3)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
	else
		return;
}

void Card3::Load(ifstream& Infile)
{
	int Cellnum;
	Infile >> Cellnum;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
	
}