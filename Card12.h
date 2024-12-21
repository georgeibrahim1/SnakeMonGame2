#pragma once
#include "Card.h"
class Card12 : public Card
{
	// Card12 Parameters:
	static int cardprice;
	static int Fees;

public:
	Card12(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void GetCopy(Grid* pGrid);


	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile, int);
	virtual void Load(ifstream& Infile);


	virtual ~Card12(); // A Virtual Destructor
};

