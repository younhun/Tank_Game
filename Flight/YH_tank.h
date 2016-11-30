#pragma once
#include "YH_object.h"

class CTank : public CObject
{
public:
	CTank();
	void MoveLeft();//왼쪽
	void MoveRight();//오른쪽
	void ShootMissile();//미사일발사
	void Print();//출력
private:
	void gotoxy(int x, int y);//좌표로 이동
	void SetColor(int color);//색 정의
	int CheckColor(int color);//색 확인
};