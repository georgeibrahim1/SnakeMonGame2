#include "Snake.h"
#include "Player.h"
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	///DONE: Do the needed validation
	if (endCellPos.IsValidCell())
	{
		//if (startCellPos.HCell() == endCellPos.HCell())
		//{
			//if (startCellPos.GetCellNum() > endCellPos.GetCellNum())
				this->endCellPos = endCellPos;
			//else
				//return;
		//}
		//else
			//return;
	}
	else
		return;
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///Done (but George will add more validations soon ) : Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a snake. Click to continue ..." and wait mouse click

	// 2- Apply the snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->PrintErrorMessage("You have reached a snake. Click to continue ...");
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	GameObject* existingLadder_or_Snake_or_Card = (pPlayer->GetCell())->GetGameObject();
	if ((pPlayer->GetCell())->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
		existingLadder_or_Snake_or_Card->Apply(pGrid, pPlayer);



}
/*
void Snake::Save(ofstream& OutFile, ObjType fromout)
{
	if (fromout == Snake_enum)
	{
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum();
	}
	else
		return;
}
*/


bool Snake::IsOverlapping(GameObject* newObj) const
{
	Snake* otherSnake = dynamic_cast<Snake*>(newObj);
	
		if (!otherSnake)
			return false;

		if ((this->position.HCell() == otherSnake->position.HCell())&& (this->endCellPos.HCell() == otherSnake->endCellPos.HCell()))
		{
			if (((this->position.VCell() <= otherSnake->endCellPos.VCell()) && (this->endCellPos.VCell() >= otherSnake->position.VCell())))
			{
			return true;
			}
		}
		return false;
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

Snake::~Snake()
{
}
