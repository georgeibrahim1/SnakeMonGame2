#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum) , turnCount(0)
{
	if (pCell)
		this->pCell = pCell;
	else
		return;
	
	if (!(playerNum >= 0 && playerNum <= 3)) 
		return;  
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet >= 0)
	{
		this->wallet = wallet;
	}
	else
		wallet = 0;
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::ResetTurnCount() 
{
		turnCount = 0;	
}

void Player::ResetStepCount()
{
	stepCount = 0;
}

int Player::GetPlayerNum() const
{
	return playerNum;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	if (pOut == nullptr) 
		return;

	color playerColor = UI.PlayerColors[playerNum];

	CellPosition playerCellPos = pCell->GetCellPosition(); 

	pOut->DrawPlayer(playerCellPos ,playerNum , playerColor);

	///DONE: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	if (pOut == nullptr)
		return;

	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;

	CellPosition playerCellPos = pCell->GetCellPosition();
	
	pOut->DrawPlayer(playerCellPos, playerNum, cellColor);
	
	///DONE: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///DONE: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	
	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	// 6- Apply() the game object of the reached cell (if any)

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

	++turnCount; 
	justRolledDiceNum = diceNumber;

	if (turnCount == 3)
	{
		wallet += 10*diceNumber;
		turnCount = 0; 
		pGrid->PrintErrorMessage("Wallet Recharge Turn: Player " + to_string(playerNum) + " gained " + to_string(10 * diceNumber) +  " and didn't move " +" , Click to continue");
		return;
	}

	if (wallet == 0)
	{
		pGrid->PrintErrorMessage("Player" + to_string(playerNum) +"'s wallet is zero, so he can't move ...." + ", Click to continue ");
		return;
	}

	CellPosition pos = pCell->GetCellPosition();

	if (pos.GetCellNum() >= 93)
	{
		if ((pos.GetCellNum() + diceNumber ) >= 99)
		{
			pGrid->SetEndGame(true);
			CellPosition FinalCell(0 , 10); 
			pGrid->UpdatePlayerCell(this, FinalCell);
			stepCount = 98;
			pGrid->PrintErrorMessage("PLAYER" + to_string(playerNum) +" IS THE WINNER!!!!" + " , Click anywhere to continue...");
			return;
		}
		else
		{
			pos.AddCellNum(diceNumber);
			pGrid->UpdatePlayerCell(this, pos);
			stepCount += diceNumber;
			GameObject* existingLadder_or_Snake_or_Card = pCell->GetGameObject();
			if (pCell->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
				existingLadder_or_Snake_or_Card->Apply(pGrid, this);
		}


	}
	else
	{
		pos.AddCellNum(diceNumber);
		pGrid->UpdatePlayerCell(this, pos);
		stepCount += diceNumber;
		GameObject* existingLadder_or_Snake_or_Card = pCell->GetGameObject();
		if (pCell->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
			existingLadder_or_Snake_or_Card->Apply(pGrid, this);
	}

}

int Player::getJustRolledDice()const {
	return justRolledDiceNum;
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}