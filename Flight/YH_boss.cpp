#include "YH_boss.h"

CBoss::CBoss(){//������ score �� life ����
	SetScore(100);
	SetLife(5);
}

void CBoss::Print()//���� �׸���
{
	SetColor(CheckColor(GetLife()));//�� ������ life�� ���� ���� Ȯ���ؼ� �����Ѵ�.
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"[��3��]";
	SetColor(7);
}

void CBoss::MoveLeft()
{
	if (GetPositionX() < 5)//���� X��ǥ 5�̻��� �������� �����δ�.=>ũ����
	{
	}
	else
	{
		SetColor(CheckColor(GetLife()));//life�� ���� �� Ȯ���� ����
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"       ";//�������� �������� �����.
		SetPositionX(GetPositionX() - 5);//"     "���� ���� X ���� X�� 5��ŭ ���� ���� ��� => ���� ũ�⿡ ���� ũ�� ����
		gotoxy(GetPositionX(), GetPositionY());//�� ��ġ���� ���� ����Ѵ�.
		cout<<"[��3��]";
		SetColor(7);
	}
}

void CBoss::MoveRight()
{
	if (GetPositionX() > 42)//���� X��ǥ 42�̻��� �������� �����δ�.=>ũ����
	{
	}
	else
	{
		SetColor(CheckColor(GetLife()));//life�� ���� �� Ȯ���� ����
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"       ";//������ ���� �������� �����.
		SetPositionX(GetPositionX() + 5);//"     "���� ���� X ���� X�� 5��ŭ ���� ���� ��� => ���� ũ�⿡ ���� ũ�� ����
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"[��3��]";	
		SetColor(7);
	}
}

void CBoss::ShootMissile()
{
	if (GetPositionY() == 29)//�̻��� Y��ǥ�� ���� ������
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//���� �̻��� ������ ���°ɷ� ó��
		SetLife(0);// life = 0 �ٷ� �����
	}
	else//�̻����� Y��ǥ ���� ���� ����"
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//������ �ڸ��� �������� ä���

		SetPositionY(GetPositionY() + 1);//" " ���� 1���� �ؼ� �̻��� ���.
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"��";
	}
}

void CBoss::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CBoss::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CBoss::CheckColor(int color)//life�� ���� �� ��ȭ
{
	if (color == 1)              //�������� 1�̸�
	{
		return 4;				//����
	}
	else if (color == 2)		//�������� 2�̸�
	{
		return 1;				//�Ķ�
	}
	else if (color == 3)		//�������� 3�̸�
	{
		return 3;				//�ϴû�
	}
	else if (color == 4)		//�������� 4�̸�
	{
		return 3;				//�ϴû�
	}
	else if (color == 5)		//�������� 5�̸�
	{
		return 3;				//�ϴû�	
	}
}