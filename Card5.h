#pragma once
#include "Card.h"

class Card5 : public Card
{
public:
		Card5(const CellPosition& pos); // A Constructor takes card position

		virtual void Apply(Grid* pGrid, Player* pPlayer);
		
		virtual void Save(ofstream& OutFile, int);
		virtual void Load(ifstream& Infile);


		virtual ~Card5(); // A Virtual Destructor
	
};

