#include "SaveGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include <iostream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
	fileName = " ";
}

void SaveGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("SaveGrid : Type in the name of the file ....");
	fileName = pIn->GetSrting(pOut);

}

void SaveGridAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ofstream file(fileName + ".txt");

	if (file.is_open()) {
		
		pGrid->SaveAll(file , 0);
		pGrid->SaveAll(file, 1);
		pGrid->SaveAll(file, 3); //till the rest cards would be added
		pOut->PrintMessage(fileName + ".txt is saved");

		file.close();
	}
	else {
		pOut->PrintMessage("File isn't Open.....");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}

}

SaveGridAction::~SaveGridAction()
{

}
