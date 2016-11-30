#include "YH_item.h"

CItem::CItem()
{
}

void CItem::Print()
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"[¡Ø]";
}

void CItem::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

