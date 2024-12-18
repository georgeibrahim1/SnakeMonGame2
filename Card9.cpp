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
}

