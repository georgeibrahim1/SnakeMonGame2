#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v <= 8)
	{
		vCell = v;
		return true;
	}
	else
		return false;
}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	}
	else
		return false;
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if ((vCell >= 0 && vCell <= 8) && (hCell >= 0 && hCell <= 10))
	{
		return true;
	}
	else
		return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{

	int cellNumber = (8 - cellPosition.vCell) * 10 + (8 - cellPosition.vCell) + cellPosition.hCell + 1;

	return cellNumber;
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	int v, h;
	if (cellNum >= 1 && cellNum <= 99)
	{
		v = 9 - (cellNum / 11.0);
		if (cellNum % 11 == 0)
		{
			h = 10;
		}
		else
		{
			h = (cellNum % 11) - 1;
		}
	}
	else
	{
		v = -1;
		h = -1;
	}

	position.SetVCell(v);
	position.SetHCell(h);

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum)
{
	int currentcell = GetCellNum();
	int newcell = currentcell + addedNum;
	*this = GetCellPositionFromNum(newcell);
}