#include "YH_enemy.h"

CEnemy::CEnemy()//적 score 와 life 선언
{
	SetScore(10);
	SetLife(2);
}

void CEnemy::Print()//적 그리기
{
	SetColor(CheckColor(GetLife()));//life에 따른 색확인후 색 지정
	gotoxy(GetPositionX(), GetPositionY());//해당 좌표가서 출력
	cout<<"♥ㅡ♥";
	SetColor(7);
}

void CEnemy::ShootMissile()//미사일 발사
{
	if (GetPositionY() == 29)//적 미사일 Y끝으로 가면
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//" " 로 나타낸다. 없앤다.
		SetLife(0);//라이프를 0으로 지정
	}
	else// 미사일이 Y끝으로 가는 과정
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//미사일 지나간자리 지운다.

		SetPositionY(GetPositionY() + 1);//" "지운곳보다 Y+1 에서 미사일 출력
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"!";
	}
}

void CEnemy::MoveLeft()//적은 전범위 움직이니 if 로 설정 하지 않았다.(보스와 비교)
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"      ";//움직이고 난 자리를 지워야 한다, 해당 좌표 "     " 출력 => 적 크기에 따라 설정
	SetPositionX(GetPositionX() - 1);//"     "좌표 보다 X방향으로 1만큼 움직인다.
}//Print() 함수 부분에 GetPositoinX() 지정

void CEnemy::MoveRight()
{
	gotoxy(GetPositionX(), GetPositionY());//해당 좌표 "     " 출력 => 적 크기에 따라 설정
	cout<<"      ";
	SetPositionX(GetPositionX() + 1);//"     "좌표 보다 X방향으로 1만큼 움직인다.
}//Print() 함수 부분에 GetPosion() 지정

void CEnemy::MoveDown()
{
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"      ";//움직이고 난 자리를 지워야 한다, 해당 좌표 "     " 출력 => 적 크기에 따라 설정
	SetPositionY(GetPositionY() + 1);//적이 밑으로 움직이기 떄문에 Y방향으로 1만큼 크다.
}

void CEnemy::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CEnemy::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CEnemy::CheckColor(int color)//life 에 따른 색 지정
{
	if (color == 1) //life 가 1일때 
	{
		return 4;   //빨강
	}
	else if (color == 2) //life 가 2일떄
	{
		return 11;       //연하늘
	}
}
