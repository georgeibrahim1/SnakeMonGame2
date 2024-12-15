#pragma once
#include "Action.h"
class NewGameAction : public Action
{
private :


public:
	NewGameAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~NewGameAction();
};

