#include "Card10.h"
#include <iostream>
#include <chrono>
#include <thread>
int Card10::cardprice = 0;//Static variable for cardprice
int Card10::Fees = 0;//Static variable for cardprice
Card10::Card10(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10;
}

Card10::~Card10(void)
{
}

void Card10::GetCopy(Grid* pGrid)
{
	Card* c;
	c = new Card10(this->GetPosition());
	c->SetCardNumber(10);
	pGrid->SetClipboard(c);

}
void Card10::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (!pGrid->getwasexecuted(14))// Parameters of card not taken yet
	{
		pOut->PrintMessage("New CardTen ...");
		this_thread::sleep_for(chrono::seconds(1));
		pOut->PrintMessage("Please Enter Card's Price ...");
		int Flag = 0;
		cardprice = pIn->GetInteger(pOut, Flag);
		while (Flag != 0 || cardprice < 0)
		{
			pOut->PrintMessage("Invalid Input for Card's Price!");
			this_thread::sleep_for(chrono::seconds(1));
			pOut->PrintMessage("Please type in a valid Number for Card's Price ...");
			cardprice = pIn->GetInteger(pOut, Flag);
		}
		pOut->PrintMessage("Please Enter Fees paid by other players ...");
		Fees = pIn->GetInteger(pOut, Flag);
		while (Flag != 0 || Fees < 0)
		{
			pOut->PrintMessage("Invalid Input for the Fee!");
			this_thread::sleep_for(chrono::seconds(1));
			pOut->PrintMessage("Please type in a valid Number for the Fee ...");
			Fees = pIn->GetInteger(pOut, Flag);
		}
		pGrid->PrintErrorMessage("Card's Price : " + to_string(cardprice) + " , Fees : " + to_string(Fees) + " , Click to continue ...");
		pGrid->setwasexecuted(14,true);
	}
	else if (pGrid->getwasexecuted(14))// Parameters already taken
	{
		pGrid->PrintErrorMessage("Another CardTen with Card's Price : " + to_string(cardprice) + " , Fees : " + to_string(Fees) + " , Click to continue ...");
	}
	pOut->ClearStatusBar();
}
void Card10::Apply(Grid* pGrid, Player* pPlayer)
{
	static int ownernum = 5;// A static variable that will hold the player number of owner
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (!pGrid->getwasexecuted(10))// False means the card is not owned yet
	{
		int Flag = 0;
		Card::Apply(pGrid, pPlayer);
		pOut->PrintMessage("You have reached a station. Do you wish to buy this cell and all cells with the same Card Number for " + to_string(cardprice) + " coin(s)? Enter 1 if YES & 0 if NO ...");
		int yes_no = pIn->GetInteger(pOut, Flag);
		while (Flag != 0 || (yes_no != 0 && yes_no != 1))
		{
			pOut->PrintMessage("Invalid Input!");
			this_thread::sleep_for(chrono::seconds(1));
			pOut->PrintMessage("Please type in 0 or 1 only ...");
			yes_no = pIn->GetInteger(pOut, Flag);
		}
		if (yes_no)// Executes if player said yes
		{
			pGrid->setwasexecuted(10, true);//To indicate this card is owned by a player
			pPlayer->SetWallet((pPlayer->GetWallet()) - cardprice);
			pOut->PrintMessage("Player " + to_string(pPlayer->GetPlayerNum()) + " is the owner of Card 10");
			this_thread::sleep_for(chrono::seconds(2));
			ownernum = (pPlayer->GetPlayerNum());// A static variable holding the player number of owner
		}

	}
	else if (pGrid->getwasexecuted(10))// True means the card is owned 
	{
		if (ownernum != pPlayer->GetPlayerNum())
			pGrid->PrintErrorMessage("You have reached a station bought by player " + to_string(ownernum) +". Click any key to continue");
		else
			pGrid->PrintErrorMessage("You have reached your station. Click any key to continue");
		int moneyleft = pPlayer->GetWallet() - Fees;
		pPlayer->SetWallet(moneyleft);// Deduct money to pay owner
		int playernum = pPlayer->GetPlayerNum();// Taking the number of the player paying the fee to the owner in a variable "playernum"
		pGrid->SetCurrentPlayer(ownernum);// Change "current player" from the one paying fee to the owner
		pPlayer = pGrid->GetCurrentPlayer();// Changing the pointer "pPlayer" to point at the owner to increase owner's wallet
		if (moneyleft >= 0)
			pPlayer->SetWallet((pPlayer->GetWallet()) + Fees);// Increasing owner's wallet with the money deducted from the other player
		else
			pPlayer->SetWallet((pPlayer->GetWallet()) + Fees + moneyleft);
		pGrid->SetCurrentPlayer(playernum);// Get back the "current player" to the one paying the fee
		pPlayer = pGrid->GetCurrentPlayer();// Pointing back the "pPlayer" pointer to the player paying the fee

	}
}

void Card10::Save(ofstream& OutFile, int Obj)
{
	if (Obj == 10)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << cardprice << " " << Fees << endl;
	}
	else
		return;
}

void Card10::Load(ifstream& Infile)
{
	int Cellnum , CP , F;
	Infile >> Cellnum >> CP >> F;
	position.SetHCell(CellPosition::GetCellPositionFromNum(Cellnum).HCell());
	position.SetVCell(CellPosition::GetCellPositionFromNum(Cellnum).VCell());
	this->cardprice = CP; 
	this->Fees = F;
}