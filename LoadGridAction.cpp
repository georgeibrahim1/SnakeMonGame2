#include "LoadGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include "GameObject.h"
#include "Snake.h"
#include "Ladder.h"
#include "CardOne.h"
#include "Card2.h"
#include "Card3.h"
#include "Card4.h"
#include "Card5.h"
#include "Card6.h"
#include "Card7.h"
#include "Card8.h"
#include "Card9.h"
#include "Card10.h"
#include "Card11.h"
#include "Card12.h"
#include "Card13.h"


LoadGridAction::LoadGridAction(ApplicationManager* pApp) : Action(pApp)
{
	fileName = " ";
}

void LoadGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->PrintErrorMessage("LoadGrid : Click and Type the name of the file....");
	fileName = pIn->GetSrting(pOut);
}

void LoadGridAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	file.open(fileName);

	if (file.is_open()) {

		pGrid->CleanGrid();
		pOut->ClearGridArea();

		int LadderNums, SnakeNums, CardNums;
		GameObject* pObj = NULL;

		file >> LadderNums;

		for (int i = 0 ; i < LadderNums ; i++)
		{
			pObj = new Ladder(-1,-1 ); 
			pObj->Load(file);
			pGrid->AddObjectToCell(pObj); 
		}

		file >> SnakeNums;

		for (int i = 0; i < SnakeNums; i++)
		{
			pObj = new Snake(-1, -1);
			pObj->Load(file);
			pGrid->AddObjectToCell(pObj);
		}

		CellPosition pos;
		file >> CardNums;
		for (int i = 0; i < CardNums; i++) {
			int num;
			file >> num;
			switch (num)
			{
			case 1: pObj = new CardOne(pos);
				break;
			case 2: pObj = new Card2(pos);
				break;
			case 3: pObj = new Card3(pos);
				break;
			case 4: pObj = new Card4(pos);
				break;
			case 5: pObj = new Card5(pos);
				break;
			case 6: pObj = new Card6(pos);
				break;
			case 7: pObj = new Card7(pos);
				break;
			case 8: pObj = new Card8(pos);
				break;
			case 9: pObj = new Card9(pos);
				break;
			case 10: pObj = new Card10(pos);
				break;
			case 11:pObj = new Card11(pos);
				break;
			case 12: pObj = new Card12(pos);
				break;
			case 13: pObj = new Card13(pos);
				break;
			}
			pObj->Load(file); 
			pGrid->AddObjectToCell(pObj);
		}

		pGrid->PrintErrorMessage(fileName + ".txt is Loaded Succesfully , Click to continue.......");

		file.close();
	}
	else {
		pGrid->PrintErrorMessage("File isn't Open.....");
	}

}

LoadGridAction::~LoadGridAction()
{

}