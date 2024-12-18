#pragma once
#include "Action.h"
class CutCardAction : public Action
{
	CellPosition SourceCell;

public:
	CutCardAction(ApplicationManager *pApp); // A Constructor
	virtual void ReadActionParameters(); 
	virtual void Execute();
	virtual ~CutCardAction(); // Virtual Destructor
};

