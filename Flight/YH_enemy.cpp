#include "YH_enemy.h"

CEnemy::CEnemy()//�� score �� life ����
{
	SetScore(10);
	SetLife(2);
}

void CEnemy::Print()//�� �׸���
{
	SetColor(CheckColor(GetLife()));//life�� ���� ��Ȯ���� �� ����
	gotoxy(GetPositionX(), GetPositionY());//�ش� ��ǥ���� ���
	cout<<"���Ѣ�";
	SetColor(7);
}

void CEnemy::ShootMissile()//�̻��� �߻�
{
	if (GetPositionY() == 29)//�� �̻��� Y������ ����
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//" " �� ��Ÿ����. ���ش�.
		SetLife(0);//�������� 0���� ����
	}
	else// �̻����� Y������ ���� ����
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//�̻��� �������ڸ� �����.

		SetPositionY(GetPositionY() + 1);//" "��������� Y+1 ���� �̻��� ���
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"!";
	}
}

void CEnemy::MoveLeft()//���� ������ �����̴� if �� ���� ���� �ʾҴ�.(������ ��)
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"      ";//�����̰� �� �ڸ��� ������ �Ѵ�, �ش� ��ǥ "     " ��� => �� ũ�⿡ ���� ����
	SetPositionX(GetPositionX() - 1);//"     "��ǥ ���� X�������� 1��ŭ �����δ�.
}//Print() �Լ� �κп� GetPositoinX() ����

void CEnemy::MoveRight()
{
	gotoxy(GetPositionX(), GetPositionY());//�ش� ��ǥ "     " ��� => �� ũ�⿡ ���� ����
	cout<<"      ";
	SetPositionX(GetPositionX() + 1);//"     "��ǥ ���� X�������� 1��ŭ �����δ�.
}//Print() �Լ� �κп� GetPosion() ����

void CEnemy::MoveDown()
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"      ";//�����̰� �� �ڸ��� ������ �Ѵ�, �ش� ��ǥ "     " ��� => �� ũ�⿡ ���� ����
	SetPositionY(GetPositionY() + 1);//���� ������ �����̱� ������ Y�������� 1��ŭ ũ��.
}

void CEnemy::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CEnemy::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CEnemy::CheckColor(int color)//life �� ���� �� ����
{
	if (color == 1) //life �� 1�϶� 
	{
		return 4;   //����
	}
	else if (color == 2) //life �� 2�ϋ�
	{
		return 11;       //���ϴ�
	}
}
