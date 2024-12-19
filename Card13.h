#pragma once
#include "Card.h"
class Card13 : public Card
{
	// Card13 Parameters:
	static int cardprice;
	static int Fees;

public:
	Card13(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual ~Card13(); // A Virtual Destructor
};
