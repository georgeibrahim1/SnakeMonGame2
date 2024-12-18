#pragma once

#include "Action.h"

class SwitchToDesignMode :public Action
{
private:


public:

	SwitchToDesignMode(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~SwitchToDesignMode();

};

