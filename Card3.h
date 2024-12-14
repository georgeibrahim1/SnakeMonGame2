#pragma once
#include "Card.h"
class Card3 : public Card
{
	// No Parameters
public:
	Card3(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of Card3 on the passed Player
	// Moves the player forward to the start of the next ladder. (If no ladders ahead, nothing)

	virtual ~Card3(); // A Virtual Destructor

};

