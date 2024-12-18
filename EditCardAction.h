#pragma once
#include "Action.h"
class EditCardAction : public Action
{

	// [Action Parameters]
	CellPosition cardPosition; //  cell position of the card

	// Note: These parameters should be read in ReadActionParameters()

public:
	EditCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads EditCardAction action parameters (cardPosition)

	virtual void Execute(); // edit the card in the cell that the user chooses.

	virtual ~EditCardAction(); // A Virtual Destructor
};

