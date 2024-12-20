#pragma once
#include "Card.h"

class Card6 : public Card
{
public:
	Card6(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile, int);
	virtual void Load(ifstream& Infile);


	virtual ~Card6(); // A Virtual Destructor

};
