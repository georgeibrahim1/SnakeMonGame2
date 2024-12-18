#include "Ladder.h"
#include "Player.h"

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
	GameObject* existingLadder_or_Snake_or_Card = (pPlayer->GetCell())->GetGameObject();
	if ((pPlayer->GetCell())->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
		existingLadder_or_Snake_or_Card->Apply(pGrid, pPlayer);
	
}

bool Ladder::IsOverlapping(GameObject* newObj) const
{
	Ladder* otherLadder = dynamic_cast<Ladder*>(newObj);
	
		if (!otherLadder)
			return false;
		if ((this->position.HCell() == otherLadder->position.HCell()) && (this->endCellPos.HCell() == otherLadder->endCellPos.HCell()))
		{
			if (((this->position.VCell() >= otherLadder->endCellPos.VCell()) && (this->endCellPos.VCell() <= otherLadder->position.VCell())))
			{
				return true;
			}
		}
		return false;		
}
/*
void Ladder::Save(ofstream& OutFile , ObjType fromout)
{
	if (fromout == Ladder_enum)
	{
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() ;
	}
	else
		return;
}
*/

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
