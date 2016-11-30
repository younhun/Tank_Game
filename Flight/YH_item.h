#pragma once
#include "YH_object.h"

class CItem : public CObject
{
public:
	CItem();//초기화
	void Print();//출력
private:
	void gotoxy(int x, int y);
};

