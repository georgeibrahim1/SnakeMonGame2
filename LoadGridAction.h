#pragma once
#include "Action.h"
class LoadGridAction : public Action
{

public:
	virtual void ReadActionParameters();
	virtual void Execute();
};

