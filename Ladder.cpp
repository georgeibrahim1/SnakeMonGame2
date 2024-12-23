#include "Ladder.h"
#include "Snake.h"
#include "Player.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{

	///DONE : Do the needed validation
	if (endCellPos.IsValidCell())
	{
				this->endCellPos = endCellPos;	
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

bool Ladder::Check_snakeendcell_ladderendcell(GameObject* newObj)
{
	if (dynamic_cast<Ladder*>(this) && dynamic_cast<Snake*>(newObj))
	{
		Snake* otherSnake = dynamic_cast<Snake*>(newObj);
		if (otherSnake->GetPosition().HCell() == this->endCellPos.HCell() && otherSnake->GetPosition().VCell() == this->endCellPos.VCell())
		{
			return true;
		}
		return false;
	}
	return false;
}

void Ladder::Save(ofstream& OutFile , int fromout)
{
	if (fromout == -1)
	{
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl ;
	}
	else
		return;
}

void Ladder::Load(ifstream& Infile)
{
	int SCellnum, eCellnum;
	Infile >> SCellnum >> eCellnum;
	position.SetHCell(CellPosition::GetCellPositionFromNum(SCellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(SCellnum).VCell());
	this->endCellPos.SetHCell(CellPosition::GetCellPositionFromNum(eCellnum).HCell());
	this->endCellPos.SetVCell(CellPosition::GetCellPositionFromNum(eCellnum).VCell());
}


CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
