#pragma once
#include <iostream>
#include <Windows.h>//gotoxy , setcolor ��
#include <conio.h>//key �Է�
#include <time.h>//srand 
#include <vector>//���� => �迭�� �����ϴ� ������� �ø��ų� ���ϼ� �ִ�.

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