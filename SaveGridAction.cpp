#include "SaveGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include "GameObject.h"

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
	fileName = " ";
}

void SaveGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->PrintErrorMessage("SaveGrid : Click and Type the name of the file....");
	fileName = pIn->GetSrting(pOut); //Get the name of the file

}

void SaveGridAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	file.open(fileName); //open the file

	if (file.is_open()) {
		file << pGrid->getNumOfObjects(-1) << endl; //num of ladders
		pGrid->SaveAll(file , -1); 
		file << pGrid->getNumOfObjects(-2) << endl; //num of snakes
		pGrid->SaveAll(file, -2);
		file << pGrid->getNumOfObjects(1) << endl; //All Cards not only CardOne , Cause It do this operation in ELSE Scope
		pGrid->SaveAll(file, 1);
		pGrid->SaveAll(file, 2);
		pGrid->SaveAll(file, 3);
		pGrid->SaveAll(file, 4);
		pGrid->SaveAll(file, 5);
		pGrid->SaveAll(file, 6);
		pGrid->SaveAll(file, 7);
		pGrid->SaveAll(file, 8);
		pGrid->SaveAll(file, 9);
		pGrid->SaveAll(file, 10);
		pGrid->SaveAll(file, 11);
		pGrid->SaveAll(file, 12);
		pGrid->SaveAll(file, 13);
		pGrid->PrintErrorMessage(fileName + ".txt is saved");

		file.close();
	}
	else {
		pGrid->PrintErrorMessage("File isn't Open.....");
	}

}

SaveGridAction::~SaveGridAction()
{

}
