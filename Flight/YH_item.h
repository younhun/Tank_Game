#pragma once
#include "YH_object.h"

class CItem : public CObject
{
public:
	CItem();//�ʱ�ȭ
	void Print();//���
private:
	void gotoxy(int x, int y);
};

