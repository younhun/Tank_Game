#include "YH_tank.h"


CTank::CTank()
{
	SetLife(3);
}

void CTank::MoveLeft()
{
	if (GetPositionX() == 0)//������
	{	
	}
	else
	{
		SetColor(CheckColor(GetLife()));
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"    ";//�������ΰ��� ���� �ڸ��� " "��������� ���
		SetPositionX(GetPositionX() - 1);
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"[��]";//�������� ������ ������ ��ũ ���
		SetColor(7);
	}
}

void CTank::MoveRight()
{
	if (GetPositionX() == 51)//����
	{	
	}
	else
	{
		SetColor(CheckColor(GetLife()));
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"    ";//�����ʵ� ��������
		SetPositionX(GetPositionX() + 1);
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"[��]";//��������
		SetColor(7);
	}
}

void CTank::Print()//��ũ ���
{
	SetColor(CheckColor(GetLife()));
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"[��]";
	SetColor(7);
}

void CTank::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CTank::ShootMissile()//�̻���
{
	if (GetPositionY() == 0)//Y�� 0 ������ ��
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"  ";//�̻����� " "�� ����Ѵ�./
		SetLife(0);//�̻����� Y�� 0 ��ǥ ������ �ٷ� �״´�(�Ҹ�) ���� 2�̸� ���ڸ��� �����־� ���� ������ 2��ŭ �������� ��´�.
	}
	else
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"  ";//�̻����� ������ �ڸ��� " " �� ���

		SetPositionY(GetPositionY() - 1);//�̻����� �� ���� Y��ǥ���� -1 �̸� �̻��� ���
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"��";
	}
}

void CTank::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CTank::CheckColor(int color)
{
	if (color == 1)
	{
		return 4;
	}
	else if (color == 2)
	{
		return 2;
	}
	else if (color == 3)
	{
		return 2;
	}
		else if (color == 4)
	{
		return 2;
	}
		else if (color == 5)
	{
		return 2;
		}

}