#pragma once
#include "YH_object.h"

class CTank : public CObject
{
public:
	CTank();
	void MoveLeft();//����
	void MoveRight();//������
	void ShootMissile();//�̻��Ϲ߻�
	void Print();//���
private:
	void gotoxy(int x, int y);//��ǥ�� �̵�
	void SetColor(int color);//�� ����
	int CheckColor(int color);//�� Ȯ��
};