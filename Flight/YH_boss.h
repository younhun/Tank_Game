#pragma once
#include "YH_object.h"

class CBoss : public CObject
{
public:
	CBoss();//�ʱ�ȭ
	void Print();//�׸���
	void MoveLeft();//���� �����̱�
	void MoveRight();//������ �����̱�
	void ShootMissile();//�̻��� �߽�
private:
	void gotoxy(int x, int y);
	void SetColor(int color);//�� ���ϱ�
	int CheckColor(int color);//�� Ȯ��
	int randVariable;///�̻��� �߻� ����
	int shootVariable;//�̻��� �߻�
};