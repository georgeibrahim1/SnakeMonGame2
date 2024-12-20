#pragma once
#include "Card.h"
class Card9 : public Card
{
	// Card9 Parameters:
	int cellnum; // the wallet value to decrease from the player

public:
	Card9(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile, int);
	virtual void Load(ifstream& Infile);


	virtual ~Card9(); // A Virtual Destructor
};


