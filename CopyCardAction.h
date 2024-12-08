#pragma once
#include "Action.h"
class CopyCardAction : public Action
{
	CellPosition SourceCell;

public:
	CopyCardAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~CopyCardAction();
};


