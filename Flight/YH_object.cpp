#include "YH_object.h"


CObject::CObject():shootVariable(0){}

void CObject::SetPositionX(int x)
{
	CObject::x = x;
}

void CObject::SetPositionY(int y)
{
	CObject::y = y;
}

void CObject::SetLife(int life)
{
	CObject::life = life;
}

void CObject::SetScore(int point)
{
	CObject::score = point;
}

int const CObject::GetPositionX()
{
	return CObject::x;
}

int const CObject::GetPositionY()
{
	return CObject::y;
}

int const CObject::GetLife()
{
	return CObject::life;
}

int const CObject::GetScore()
{
	return CObject::score;
}

void CObject::Print()
{
}

void CObject::ShootMissile()
{
}

void CObject::MoveLeft()
{
}

void CObject::MoveRight()
{
}

void CObject::SetRandVariable(int num)
{
	CObject::randVariable = num;
}

int const CObject::GetRandVariable()
{
	return CObject::randVariable;
}

void CObject::SetShootVariable(int num)
{
	CObject::shootVariable = num;
}

int const CObject::GetShootVariable()
{
	return CObject::shootVariable;
}