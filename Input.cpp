#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->FlushKeyQueue();
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO, int& flag) const // return is valid only when flag = 0 , range of return:0 to 999999999(written by team)
{
	///TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()
	int i = 0;
	int k = 0; // counts how many zeros are at the start of the string
	flag = 0;
	string Label = Input::GetSrting(pO);
	int len = Label.length(); // actual length of string
	int lenRange = len; // Range of integers that needs to be 9 or less
	while (Label[i] == '0' && i < len)
	{
		i++;
		k++;
	}
	lenRange = len - k;
	if (lenRange > 9)
	{
		flag = -1; // user entered more than 9 characters .To ensure the input is in range of int (written by team)
	}
	if (len == 0)
	{
		flag = -2; // user entered an empty string (written by team)
	}

	while (i < len && flag == 0)
	{
		if (Label[i] < '0' || Label[i] > '9')
			flag = 1; // user entered a non integer character (written by team)
		i++;
	}
	if (flag == 0)
	{
		int string_to_int = stoi(Label);
		return string_to_int;
	}
	else
		return -1; // IMPORTANT: -1 doesn't represent anything and shouldn't be used in main. (written by team) 


	// this line should be changed with your implementation

	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)


	 // this line should be changed with your implementation
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;
			case ITM_COPY_CARD: return COPY_CARD;
			case ITM_PASTE_CARD: return PASTE_CARD;
			case ITM_CUT_CARD: return CUT_CARD;
			case ITM_EDIT_CARD: return EDIT_CARD;
			case ITM_DELETE_OBJECT: return DELETE_OBJECT;
			case ITM_SAVE_GRID: return SAVE_GRID;
			case ITM_LOAD_GRID: return LOAD_GRID;
			case ITM_EXIT_DM: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;


				///DONE: Add cases for the other items of Design Mode




			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType

		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ROLL_DICE: return ROLL_DICE;
			case ITM_INPUT_DICE_VALUE: return INPUT_DICE_VALUE;
			case ITM_NEW_GAME: return NEW_GAME;
			case ITM_EXIT_PM: return EXIT;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;


				///DONE: Add cases for the other items of Design Mode

			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;




	}

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			cellPos.SetVCell((y - UI.ToolBarHeight) / UI.CellHeight);
			cellPos.SetHCell((x) / UI.CellWidth); ///DONE: SetHCell and SetVCell of the object cellPost appropriately
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)



		}
	}

	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 

