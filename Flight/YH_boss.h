#pragma once
#include "YH_object.h"

class CBoss : public CObject
{
public:
	CBoss();//초기화
	void Print();//그리기
	void MoveLeft();//왼쪽 움직이기
	void MoveRight();//오른쪽 움직이기
	void ShootMissile();//미사일 발싸
private:
	void gotoxy(int x, int y);
	void SetColor(int color);//색 정하기
	int CheckColor(int color);//색 확인
	int randVariable;///미사일 발사 간격
	int shootVariable;//미사일 발사
};