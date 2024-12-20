#pragma once
#include "Action.h"
#include <fstream>

class SaveGridAction : public Action
{
private:
	string fileName;
	ofstream file;


public:
	SaveGridAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~SaveGridAction();
};
