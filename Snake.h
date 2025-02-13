#pragma once

#include "GameObject.h"

class Snake : public GameObject
{
	CellPosition endCellPos; 
public:
	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the snake by moving player to snake's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	virtual bool IsOverlapping(GameObject* newObj) const;
	virtual bool Check_snakeendcell_ladderendcell(GameObject* newObj);
	virtual void Save(ofstream& OutFile, int);
	virtual void Load(ifstream& Infile);

	virtual ~Snake(); // Virtual destructor
};

