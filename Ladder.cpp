#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{

	///DONE : Do the needed validation
	if (endCellPos.IsValidCell())
	{
		//if (startCellPos.HCell() == endCellPos.HCell())
		//{
			//if (startCellPos.GetCellNum() < endCellPos.GetCellNum())
				this->endCellPos = endCellPos;
			///else
				//return; 
		//}
		//else
			//return;
	}
	else
		return;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///Done (but George will add more validations soon ) : Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	   
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
    pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}

bool Ladder::IsOverlapping(GameObject* newObj) const
{
	Ladder* otherLadder = dynamic_cast<Ladder*>(newObj);
	if ((this->position.HCell() == otherLadder->position.HCell()) && (this->endCellPos.HCell() == otherLadder->endCellPos.HCell()))
	{
		if (!otherLadder)
			return false;


		if ((this->position.VCell() <= otherLadder->position.VCell()) && (this->position.VCell() >= otherLadder->endCellPos.VCell()) ||
			(this->endCellPos.VCell() <= otherLadder->position.VCell()) && (this->endCellPos.VCell() >= otherLadder->endCellPos.VCell()))
		{
			return true;
		}
	}
	return false;
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
