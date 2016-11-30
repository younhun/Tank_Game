#include "YH_wall.h"

CWall::CWall()
{
}

CWall_a::CWall_a()
{
}

void CWall::Print()
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"*****";
	SetColor(7);
}

void CWall_a::Print()
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"¡Ù¡Ù¡Ù";
	SetColor(7);
}

void CWall::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CWall::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CWall_a::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CWall_a::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}