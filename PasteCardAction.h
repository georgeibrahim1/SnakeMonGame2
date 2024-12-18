#pragma once
#include "Action.h"
class PasteCardAction : public Action
{
	CellPosition DestinationCell;
public:
	PasteCardAction(ApplicationManager* pApp); // A Constructor
	virtual void ReadActionParameters(); 
	virtual void Execute();
	virtual ~PasteCardAction(); // Virtual Destructor
};

