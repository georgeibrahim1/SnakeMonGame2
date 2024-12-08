#pragma once
#include "Action.h"
class DeleteObjectAction : public Action
{
	CellPosition Pos;


public:
	DeleteObjectAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~DeleteObjectAction();

};

