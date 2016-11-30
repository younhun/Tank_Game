#include "YH_board.h"

CBoard::CBoard()
{
}

void CBoard::BPrint()//판 그리기
{
	gotoxy(22, 31);
	cout<<"Stage :     ", stage;
	gotoxy(22, 32);
	cout<<"Score :     ", gameScore;
	//score 와 stage
	gotoxy(3, 31);
	cout<<"<- : 탱크좌로이동";
	gotoxy(3, 32);
	cout<<"-> : 탱크우로이동";
	gotoxy(3, 33);
	cout<<"5 :  게임시작    ";
	gotoxy(3, 34);
	cout<<"space : 미사일   ";
	//조작법 설명
	
	for (int j = 0; j < 31; j++)//판 크기에 따른 세로줄
	{
		gotoxy(55, j);
		cout<<"│";
	}
	for (int i = 0; i < 56; i++)//판 크기에 따른 가로줄
	{
		gotoxy(i, 30);
		cout<<"-";
	}
}

void CBoard::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
