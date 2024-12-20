#pragma once
#include "Action.h"
#include <fstream>

class LoadGridAction : public Action
{
private:
	string fileName;
	ifstream file;


public:
	LoadGridAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~LoadGridAction();
};

