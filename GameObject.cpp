#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}
void GameObject:: SetPosition(const CellPosition & pos) // by team
{
	this->position = pos; // Sets Position
}

bool GameObject::IsOverlapping(GameObject* newObj) const
{
	return 0;
}
bool GameObject::Check_snakeendcell_ladderendcell(GameObject* newObj)
{
	return 0;
}
void GameObject::GetCopy(Grid* pGrid)
{
	
}

GameObject::~GameObject()
{
}