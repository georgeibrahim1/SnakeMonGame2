#include "Player.h"
#include "Grid.h"
#include <fstream>
#include "GameObject.h"


Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum) , turnCount(0), ToSkip(0) , AnotherRoll(0) , 
                                               burnEffectActive(false) , poisonEffectActive(false) , burnRemainingTurns(0) , poisonRemainingTurns(0)
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
		this->wallet = 0;
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
void Player::SetToSkip(bool S)
{
	ToSkip = S;
}


bool Player::GetToSkip() const
{
	return ToSkip;
}
void Player::SetAnotherRoll(bool S)
{
	AnotherRoll = S;
}


bool Player::GetAnotherRoll() const
{
	return AnotherRoll;
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

bool Player::SpecialAttack(Grid* pGrid, int attackType)
{
	if (this->GetPlayerNum() == 0)
	{
		static int specialAttacksUsedCounts0 = 0;
		static bool specialAttacksUsed0[4] = { false, false, false, false };
		if (attackType < 1 || attackType > 4 || specialAttacksUsed0[attackType - 1] || specialAttacksUsedCounts0 >= 2) {
			return false;
		}

		specialAttacksUsed0[attackType - 1] = true;
		specialAttacksUsedCounts0 += 1;

		switch (attackType) {
		case 1: {
			int flag;
			pGrid->PrintErrorMessage("Choose a player to freeze their next turn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetToSkip(1); // Prevents the player from playing their next turn
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " has been frozen for the next turn. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 2: { // Fire: Deduct 20 coins from the target for the next 3 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to burn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetBurnEffect(); // Custom method to handle the burn effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will lose 20 coins for the next 3 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 3: { // Poison: Reduce the target's dice rolls by 1 for the next 5 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to poison: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetPoisonEffect(); // Custom method to handle the poison effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will roll 1 less for the next 5 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 4: { // Lightning: Deduct 20 coins from all other players
			for (int i = 0; i < 4; ++i) {
				if (i != this->GetPlayerNum()) { // Skip the current player
					Player* other = pGrid->GetPlayer(i);
					if (other) {
						other->DeductCoins(20); // Custom method to deduct coins
					}
				}
			}
			pGrid->PrintErrorMessage("All other players lost 20 coins. Click to continue.");
			break;
		}
		default:
			return false;
		}

		return true;
	}
	else if (this->GetPlayerNum() == 1)
	{
		static int specialAttacksUsedCounts1 = 0;
		static bool specialAttacksUsed1[4] = { false, false, false, false };
		if (attackType < 1 || attackType > 4 || specialAttacksUsed1[attackType - 1] || specialAttacksUsedCounts1 >= 2) {
			return false;
		}

		specialAttacksUsed1[attackType - 1] = true;
		specialAttacksUsedCounts1 += 1;

		switch (attackType) {
		case 1: {
			int flag;
			pGrid->PrintErrorMessage("Choose a player to freeze their next turn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetToSkip(1); // Prevents the player from playing their next turn
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " has been frozen for the next turn. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 2: { // Fire: Deduct 20 coins from the target for the next 3 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to burn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetBurnEffect(); // Custom method to handle the burn effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will lose 20 coins for the next 3 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 3: { // Poison: Reduce the target's dice rolls by 1 for the next 5 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to poison: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetPoisonEffect(); // Custom method to handle the poison effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will roll 1 less for the next 5 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 4: { // Lightning: Deduct 20 coins from all other players
			for (int i = 0; i < 4; ++i) {
				if (i != this->GetPlayerNum()) { // Skip the current player
					Player* other = pGrid->GetPlayer(i);
					if (other) {
						other->DeductCoins(20); // Custom method to deduct coins
					}
				}
			}
			pGrid->PrintErrorMessage("All other players lost 20 coins. Click to continue.");
			break;
		}
		default:
			return false;
		}

		return true;
	}
	else if (this->GetPlayerNum() == 2)
	{
		static int specialAttacksUsedCounts2 = 0;
		static bool specialAttacksUsed2[4] = { false, false, false, false };
		if (attackType < 1 || attackType > 4 || specialAttacksUsed2[attackType - 1] || specialAttacksUsedCounts2 >= 2) {
			return false;
		}

		specialAttacksUsed2[attackType - 1] = true;
		specialAttacksUsedCounts2 += 1;

		switch (attackType) {
		case 1: {
			int flag;
			pGrid->PrintErrorMessage("Choose a player to freeze their next turn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetToSkip(1); // Prevents the player from playing their next turn
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " has been frozen for the next turn. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 2: { // Fire: Deduct 20 coins from the target for the next 3 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to burn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetBurnEffect(); // Custom method to handle the burn effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will lose 20 coins for the next 3 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 3: { // Poison: Reduce the target's dice rolls by 1 for the next 5 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to poison: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetPoisonEffect(); // Custom method to handle the poison effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will roll 1 for the next 5 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 4: { // Lightning: Deduct 20 coins from all other players
			for (int i = 0; i < 4; ++i) {
				if (i != this->GetPlayerNum()) { // Skip the current player
					Player* other = pGrid->GetPlayer(i);
					if (other) {
						other->DeductCoins(20); // Custom method to deduct coins
					}
				}
			}
			pGrid->PrintErrorMessage("All other players lost 20 coins. Click to continue.");
			break;
		}
		default:
			return false;
		}

		return true;
	}
	else if (this->GetPlayerNum() == 3)
	{
		static int specialAttacksUsedCounts3 = 0;
		static bool specialAttacksUsed3[4] = { false, false, false, false };
		if (attackType < 1 || attackType > 4 || specialAttacksUsed3[attackType - 1] || specialAttacksUsedCounts3 >= 2) {
			return false;
		}

		specialAttacksUsed3[attackType - 1] = true;
		specialAttacksUsedCounts3 += 1;

		switch (attackType) {
		case 1: {
			int flag;
			pGrid->PrintErrorMessage("Choose a player to freeze their next turn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetToSkip(1); // Prevents the player from playing their next turn
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " has been frozen for the next turn. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 2: { // Fire: Deduct 20 coins from the target for the next 3 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to burn: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetBurnEffect(); // Custom method to handle the burn effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will lose 20 coins for the next 3 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 3: { // Poison: Reduce the target's dice rolls by 1 for the next 5 turns
			int flag;
			pGrid->PrintErrorMessage("Choose a player to poison: ");
			int targetPlayer = pGrid->GetInput()->GetInteger(pGrid->GetOutput(), flag);
			Player* target = pGrid->GetPlayer(targetPlayer);
			if (target) {
				target->SetPoisonEffect(); // Custom method to handle the poison effect
				pGrid->PrintErrorMessage("Player " + to_string(targetPlayer) + " will roll 1 less for the next 5 turns. Click to continue.");
			}
			else {
				pGrid->PrintErrorMessage("Invalid player choice. Click to continue.");
			}
			break;
		}
		case 4: { // Lightning: Deduct 20 coins from all other players
			for (int i = 0; i < 4; ++i) {
				if (i != this->GetPlayerNum()) { // Skip the current player
					Player* other = pGrid->GetPlayer(i);
					if (other) {
						other->DeductCoins(20); // Custom method to deduct coins
					}
				}
			}
			pGrid->PrintErrorMessage("All other players lost 20 coins. Click to continue.");
			break;
		}
		default:
			return false;
		}

		return true;
	}
}

void Player::SetBurnEffect() {
	burnEffectActive = true;         // Activate the burn effect
	burnRemainingTurns = 3;     // Number of turns for the burn effect
}

void Player::SetPoisonEffect() {
	poisonEffectActive = true;       // Activate the poison effect
	poisonRemainingTurns = 5 ;   // Number of turns for the poison effect
}

void Player::DeductCoins(int D)
{
	wallet -= D; 
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

	justRolledDiceNum = diceNumber;
	++turnCount;

	if (this->GetAnotherRoll()) // indicating that the player will get another roll (without affecting the turncount)
	{
		--turnCount;
		this->SetAnotherRoll(0); // Another roll back to zero
	}

	

	if (burnEffectActive) {
		wallet -= 20;
		burnRemainingTurns--;
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " loses 20 coins due to burn effect. Click to continue.");
		if (burnRemainingTurns <= 0) {
			burnEffectActive = false; 
		}
	}

	if (this->GetToSkip()) // indicating that the player will skip this round
	{
		pGrid->PrintErrorMessage("you are denied from playing this turn.Click to continue");
		this->SetToSkip(0); // player will be able to play normally in the next round

		return;
	}

	if (poisonEffectActive) {
		justRolledDiceNum = 1;
		poisonRemainingTurns--;
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " rolls 1 due to poison effect. Click to continue.");
		if (poisonRemainingTurns <= 0) {
			poisonEffectActive = false; 
		}
	}

	if (turnCount == 3) {

		pGrid->PrintErrorMessage("Do you wish to launch a special attack instead of recharging? (y/n) , Click to Input .......");
		string choice = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
		if (choice == "y" || choice == "Y") {
			int flag;
			pGrid->PrintErrorMessage("Choose your special attack : 1.Ice    2.Fire    3.Poison    4.Lightning , Click to Input .......");
			int attackType = pGrid->GetInput()->GetInteger(pGrid->GetOutput() ,flag );
			if (this->SpecialAttack(pGrid, attackType)) {
				turnCount = 0;
				return;
			}
			else {
				pGrid->PrintErrorMessage("You Can't Attack , Recharging wallet...");
			}
		}
			pGrid->PrintErrorMessage("Recharging wallet...");
			wallet += 10 * justRolledDiceNum;
			turnCount = 0;
			pGrid->PrintErrorMessage("Wallet Recharge Turn: Player " + to_string(playerNum) + " gained " + to_string(10 * justRolledDiceNum) + " and didn't move. Click to continue.");
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
		if ((pos.GetCellNum() + justRolledDiceNum) >= 99)
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
			pos.AddCellNum(justRolledDiceNum);
			pGrid->UpdatePlayerCell(this, pos);
			stepCount += justRolledDiceNum;
			GameObject* existingLadder_or_Snake_or_Card = pCell->GetGameObject();
			if (pCell->GetGameObject()) // checks if the cell has a ladder or snake or card, if it points to null don't call apply()
				existingLadder_or_Snake_or_Card->Apply(pGrid, this);
		}


	}
	else
	{
		pos.AddCellNum(justRolledDiceNum);
		pGrid->UpdatePlayerCell(this, pos);
		stepCount += justRolledDiceNum;
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