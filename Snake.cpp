#include "Snake.h"
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

}

bool Snake::IsOverlapping(GameObject* newObj) const
{
	Snake* otherSnake = dynamic_cast<Snake*>(newObj);
	if (!otherSnake)
		return false;


	if ((this->position.VCell() >= otherSnake->position.VCell()) && (this->position.VCell() <= otherSnake->endCellPos.VCell()) ||
		(this->endCellPos.VCell() >= otherSnake->position.VCell()) && (this->endCellPos.VCell() <= otherSnake->endCellPos.VCell()))
	{
		return false;
	}

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

Snake::~Snake()
{
}