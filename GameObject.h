#pragma once


#include "CellPosition.h"
#include "Grid.h"
#include "Player.h"
#include "Output.h"
#include <fstream>

class Grid;
class Player;

// Base Class for All Game Objects ( ladders, snakes and cards )
class GameObject
{

protected:

	CellPosition position; // The current cell position of the GameObject

public:

	GameObject(const CellPosition& pos); // Constructor for initializing data members

	CellPosition GetPosition() const;     // A Getter for position
	void SetPosition(const CellPosition& pos); // by Team, A Setter for Position

	// ============ Virtual Functions ============

	virtual void Draw(Output* pOut) const = 0;	 // Draws the game object in the window in his position cell 
	// (drawing depends on GameObject Type, so virtual)

	virtual void Apply(Grid* pGrid, Player* pPlayer) = 0;  // Applys the effect of the GameObject on the passed Player
	// (The effect depends on the GameObject type, so virtual)
	// For example, applying a ladder is by moving player up, and so on

// The following functions are examples of what should be supported by the GameObject class
// They should be overridden by each inherited class

// Decide the parameters that you should pass to each function	

	virtual void Save(ofstream& OutFile, int) = 0;	// Saves the GameObject parameters to the file
	virtual void Load(ifstream &Infile) = 0;	// Loads and Reads the GameObject parameters from the file

	// checks if the cell has a 
	virtual bool IsOverlapping(GameObject* newObj) const;
	virtual bool Check_snakeendcell_ladderendcell(GameObject*);
	virtual void GetCopy(Grid* pGrid);
	virtual ~GameObject(); // Virtual destructor
};

