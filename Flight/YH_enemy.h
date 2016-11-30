#pragma once
#include "YH_object.h"

class CEnemy : public CObject
{
public:
	CEnemy();//초기화
	void Print();//출력
	void ShootMissile();//미사일 발사
	void MoveLeft();//왼쪽
	void MoveRight();//오른쪽
	void MoveDown();//아래
protected:
	void gotoxy(int x, int y);
	void SetColor(int color);//색 결정
	int CheckColor(int color);//life 에 따른 색확인
};
