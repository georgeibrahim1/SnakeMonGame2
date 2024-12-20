#pragma once
#include "Card.h"
class Card7 : public Card
{
	// No Parameters
public:
	Card7(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of Card7 on the passed Player
	// Gives the player another dice roll.

	virtual void Save(ofstream& OutFile, int);
	virtual void Load(ifstream& Infile);

	virtual ~Card7(); // A Virtual Destructor
};

