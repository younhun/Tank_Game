#include "YH_over.h"
#include "YH_game.h"
COver::COver()
{
}

void COver::GameOver()
{
	CGame game_;
	system("cls");	
	gotoxy(22,10);
	cout<<"Press [anything] to Restart...";
	getch();
	game_.Run();
	//������� Ű���� �Է��������� ���� ����
}

void COver::gotoxy(int x, int y)
{ 
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}