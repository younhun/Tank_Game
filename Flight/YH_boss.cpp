#include "YH_boss.h"

CBoss::CBoss(){//보스의 score 와 life 설정
	SetScore(100);
	SetLife(5);
}

void CBoss::Print()//보스 그리기
{
	SetColor(CheckColor(GetLife()));//색 결정의 life에 따른 색을 확인해서 결정한다.
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"[♥3♥]";
	SetColor(7);
}

void CBoss::MoveLeft()
{
	if (GetPositionX() < 5)//보스 X좌표 5이상인 구간에서 움직인다.=>크기고려
	{
	}
	else
	{
		SetColor(CheckColor(GetLife()));//life에 따른 색 확인후 지정
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"       ";//왼쪽으로 지나간길 지운다.
		SetPositionX(GetPositionX() - 5);//"     "에서 지정 X 보다 X축 5만큼 가서 보스 출력 => 보스 크기에 따른 크기 지정
		gotoxy(GetPositionX(), GetPositionY());//그 위치에서 보스 출력한다.
		cout<<"[♥3♥]";
		SetColor(7);
	}
}

void CBoss::MoveRight()
{
	if (GetPositionX() > 42)//보스 X좌표 42이상인 구간에서 움직인다.=>크기고려
	{
	}
	else
	{
		SetColor(CheckColor(GetLife()));//life에 따른 색 확인후 지정
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"       ";//오른쪽 으로 지나간길 지운다.
		SetPositionX(GetPositionX() + 5);//"     "에서 지정 X 보다 X축 5만큼 가서 보스 출력 => 보스 크기에 따른 크기 지정
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"[♥3♥]";	
		SetColor(7);
	}
}

void CBoss::ShootMissile()
{
	if (GetPositionY() == 29)//미사일 Y좌표가 끝에 닿을때
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//보스 미사일 끝에는 없는걸로 처리
		SetLife(0);// life = 0 바로 사라짐
	}
	else//미사일이 Y좌표 끝에 갈때 까지"
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<" ";//지나간 자리는 공백으로 채운다

		SetPositionY(GetPositionY() + 1);//" " 보다 1증가 해서 미사일 출력.
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"ㅜ";
	}
}

void CBoss::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CBoss::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CBoss::CheckColor(int color)//life에 따른 색 변화
{
	if (color == 1)              //라이프가 1이면
	{
		return 4;				//빨강
	}
	else if (color == 2)		//라이프가 2이면
	{
		return 1;				//파랑
	}
	else if (color == 3)		//라이프라 3이면
	{
		return 3;				//하늘색
	}
	else if (color == 4)		//라이프가 4이면
	{
		return 3;				//하늘색
	}
	else if (color == 5)		//라이프가 5이면
	{
		return 3;				//하늘색	
	}
}