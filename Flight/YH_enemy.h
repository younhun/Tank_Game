#pragma once
#include "YH_object.h"

class CEnemy : public CObject
{
public:
	CEnemy();//�ʱ�ȭ
	void Print();//���
	void ShootMissile();//�̻��� �߻�
	void MoveLeft();//����
	void MoveRight();//������
	void MoveDown();//�Ʒ�
protected:
	void gotoxy(int x, int y);
	void SetColor(int color);//�� ����
	int CheckColor(int color);//life �� ���� ��Ȯ��
};
