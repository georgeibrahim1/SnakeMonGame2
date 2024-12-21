#pragma once
#include "Card.h"
class Card8 : public Card
{
	// No Parameters
public:
	Card8(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of Card8 on the passed Player


	virtual void GetCopy(Grid* pGrid);


	virtual void Save(ofstream& OutFile, int);
	virtual void Load(ifstream& Infile);

	virtual ~Card8(); // A Virtual Destructor
};

