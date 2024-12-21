#pragma once
#include "Card.h"
class Card4 : public Card
{
	// No Parameters
public:
	Card4(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of Card4 on the passed Player
	// Moves the player forward to the start of the next snake. (If no snake ahead, nothing)

	virtual void GetCopy(Grid* pGrid);

	virtual void Save(ofstream& OutFile, int);

	virtual void Load(ifstream& Infile);

	virtual ~Card4(); // A Virtual Destructor
};

