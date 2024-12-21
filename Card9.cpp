#include "Card9.h"
#include "CellPosition.h"
#include <iostream>
#include <chrono>
#include <thread>
Card9::Card9(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9;
	cellnum = 0;
}

Card9::~Card9(void)
{
}

void Card9::Setcellnum(int w)
{
	cellnum = w;
}
int Card9::Getcellnum()
{
	return cellnum;
}
void Card9::GetCopy(Grid* pGrid)
{
	Card* c;
	c = new Card9(this->GetPosition());
	c->SetCardNumber(9);
	c->Setcellnum(this->Getcellnum());
	pGrid->SetClipboard(c);

}
void Card9::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardNine: Enter the Cell Number that the player will move to ...");
	int Flag = 0;
	cellnum = pIn->GetInteger(pOut, Flag);
	while (Flag != 0 || (cellnum < 0 && cellnum>99))
	{
		pOut->PrintMessage("Invalid Input!");
		this_thread::sleep_for(chrono::seconds(1));
		pOut->PrintMessage("Please type in a valid Number ...");
		cellnum = pIn->GetInteger(pOut, Flag);
	}
	pOut->ClearStatusBar();
}
void Card9::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	CellPosition movetocell = CellPosition::GetCellPositionFromNum(cellnum);
	pGrid->UpdatePlayerCell(pPlayer, movetocell);
	GameObject* existingLadder_or_Snake_or_Card = (pPlayer->GetCell())->GetGameObject();
	if ((pPlayer->GetCell())->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
		existingLadder_or_Snake_or_Card->Apply(pGrid, pPlayer);


}

void Card9::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 9)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << cellnum << endl;
	}
	else
		return;
}

void Card9::Load(ifstream& Infile)
{
	int Cellnum;
	Infile >> Cellnum;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
}
