#include "YH_board.h"

CBoard::CBoard()
{
}

void CBoard::BPrint()//�� �׸���
{
	gotoxy(22, 31);
	cout<<"Stage :     ", stage;
	gotoxy(22, 32);
	cout<<"Score :     ", gameScore;
	//score �� stage
	gotoxy(3, 31);
	cout<<"<- : ��ũ�·��̵�";
	gotoxy(3, 32);
	cout<<"-> : ��ũ����̵�";
	gotoxy(3, 33);
	cout<<"5 :  ���ӽ���    ";
	gotoxy(3, 34);
	cout<<"space : �̻���   ";
	//���۹� ����
	
	for (int j = 0; j < 31; j++)//�� ũ�⿡ ���� ������
	{
		gotoxy(55, j);
		cout<<"��";
	}
	for (int i = 0; i < 56; i++)//�� ũ�⿡ ���� ������
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
