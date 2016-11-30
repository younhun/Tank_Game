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
	//종료된후 키보드 입력이있으면 게임 실행
}

void COver::gotoxy(int x, int y)
{ 
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}