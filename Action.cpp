#include "Action.h"
#include "CardOne.h"

Action::Action(ApplicationManager *pApp) : pManager(pApp)
{
	// The constructor initializes the ApplicationManager pointer data member
}
Card* Action :: SwitchCases(Card* pCard, int CardNumber, CellPosition pos)
{
	switch (CardNumber)
	{
	case 1:
		pCard = new CardOne(pos);
		return pCard;
		break;

		// A- Add the remaining cases

	}

}
Action::~Action()
{
}

