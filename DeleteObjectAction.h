#pragma once
#include "Action.h"
class DeleteObjectAction : public Action
{
	CellPosition Pos;


public:
	DeleteObjectAction(ApplicationManager* pApp); // A Constructor
	virtual void ReadActionParameters(); 
	virtual void Execute();
	virtual ~DeleteObjectAction();// Virtual Destructor

};

