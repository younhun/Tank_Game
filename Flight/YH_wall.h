#pragma once
#include "YH_object.h"

class CWall : public CObject
{
public:
	CWall();
	void Print();
private:
	void gotoxy(int x, int y);
	void SetColor(int color);
};

class CWall_a : public CObject
{
public:
	CWall_a();
	void Print();
private:
	void gotoxy(int x, int y);
	void SetColor(int color);
};
