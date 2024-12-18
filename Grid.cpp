#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========

bool Grid::IsOverlapping(GameObject* newObj) const {
	for (int v = 0; v < NumVerticalCells; ++v) {
		for (int h = 0; h < NumHorizontalCells; ++h) {
			GameObject* existingObj = CellList[v][h]->GetGameObject();
			if (existingObj && existingObj->IsOverlapping(newObj)) {
				return true; 
			}
		}
	}
	return false; 
}

bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);
	
	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	
	
	// Draw the player's circle on the new cell position
	player->Draw(pOut);

}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

void Grid::SetCurrentPlayer(int PlayerNum)
{
	if (PlayerNum >= 0 && PlayerNum < MaxPlayerCount)
		currPlayerNumber = PlayerNum;
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///DONE: Check if CellList[i][j] has a ladder, if yes return it
			if(CellList[i][j]->HasLadder())
				return CellList[i][j]->HasLadder();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}
Snake* Grid::GetNextSnake(const CellPosition& position) // Added by Team
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the Snake in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///DONE: Check if CellList[i][j] has a Snake, if yes return it
			if (CellList[i][j]->HasSnake())
				return CellList[i][j]->HasSnake();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}
bool Grid::HasObject(CellPosition pos)  // by team, check for class responsibilit y
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return true;
		else 
			return false; // Cell doesn't contain an oject
	}
	return false; // if not a valid position
}
Card* Grid::HasCard(CellPosition pos)  // by team, check for class responsibility
{
	if (pos.IsValidCell()) // Check if valid position
		return CellList[pos.VCell()][pos.HCell()]->HasCard();
	else
		return NULL;

}

void Grid::ResetGame()
{
	endGame = 0;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player* pPlayer = PlayerList[i];

		Cell firstcell(8,0);
		
		UpdatePlayerCell(pPlayer, firstcell.GetCellPosition() );

		pPlayer->SetWallet(100);

		pPlayer->ResetTurnCount();

		pPlayer->ResetStepCount();
	}

	SetCurrentPlayer(0);
}
/*
int Grid::getNumOfObjects(ObjType Object) //I will change it till all cards are done
{
	int NumofObject = 0;

	if (Object == Ladder_enum)
	{
		for (int v = 0; v < NumVerticalCells; ++v)
		{
			for (int h = 0; h < NumHorizontalCells; ++h)
			{
				if (CellList[v][h]->HasLadder())
				{
					NumofObject++;
					
				}
			}
		}
	}
	else if (Object == Snake_enum)
	{
		for (int v = 0; v < NumVerticalCells; ++v)
		{
			for (int h = 0; h < NumHorizontalCells; ++h)
			{
				if (CellList[v][h]->HasSnake())
				{
					NumofObject++;

				}
			}
		}
	}
	else
	{
		for (int v = 0; v < NumVerticalCells; ++v)
		{
			for (int h = 0; h < NumHorizontalCells; ++h)
			{
				if (CellList[v][h]->HasCard())
				{
					NumofObject++;

				}
			}
		}
	}

	return NumofObject;
}

void Grid::SaveAll(ofstream& OutFile, ObjType fromout)
{
	OutFile << getNumOfObjects(fromout) << endl; 

	for (int v = 0; v < NumVerticalCells; ++v) 
	{
		for (int h = 0; h < NumHorizontalCells; ++h) 
		{
			if (HasObject(CellList[v][h]->GetCellPosition()))
			{
				GameObject * existingObject = CellList[v][h]->GetGameObject();
				existingObject->Save(OutFile , fromout);
			}
		}
	}
}

*/

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}
