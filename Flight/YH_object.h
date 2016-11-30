#pragma once
#include <iostream>
#include <Windows.h>//gotoxy , setcolor 등
#include <conio.h>//key 입력
#include <time.h>//srand 
#include <vector>//백터 => 배열과 유사하다 마음대로 늘리거나 줄일수 있다.

using namespace std;

class CObject
{
public:
	CObject();
	void SetPositionX(int x);
	void SetPositionY(int y);
	void SetLife(int life);
	void SetScore(int point);
	void SetRandVariable(int num);
	void SetShootVariable(int num);

	int const GetPositionX();
	int const GetPositionY();
	int const GetLife();
	int const GetScore();
	int const GetRandVariable();
	int const GetShootVariable();

	virtual void ShootMissile();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void Print();

private:
	int x;
	int y;
	int score;
	int life;
	int randVariable;
	int shootVariable;
};