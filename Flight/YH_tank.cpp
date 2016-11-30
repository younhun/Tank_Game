#include "YH_tank.h"


CTank::CTank()
{
	SetLife(3);
}

void CTank::MoveLeft()
{
	if (GetPositionX() == 0)//시작점
	{	
	}
	else
	{
		SetColor(CheckColor(GetLife()));
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"    ";//왼쪽으로가면 원래 자리는 " "빈공간으로 출력
		SetPositionX(GetPositionX() - 1);
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"[凸]";//왼쪽으로 움직일 때마다 탱크 출력
		SetColor(7);
	}
}

void CTank::MoveRight()
{
	if (GetPositionX() == 51)//끝점
	{	
	}
	else
	{
		SetColor(CheckColor(GetLife()));
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"    ";//오른쪽도 마찬가지
		SetPositionX(GetPositionX() + 1);
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"[凸]";//마찬가지
		SetColor(7);
	}
}

void CTank::Print()//탱크 출력
{
	SetColor(CheckColor(GetLife()));
	gotoxy(GetPositionX(), GetPositionY());
	cout<<"[凸]";
	SetColor(7);
}

void CTank::gotoxy(int x, int y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CTank::ShootMissile()//미사일
{
	if (GetPositionY() == 0)//Y가 0 에있을 때
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"  ";//미사일은 " "로 출력한다./
		SetLife(0);//미사일이 Y가 0 좌표 갔을떄 바로 죽는다(소멸) 만약 2이면 그자리에 남아있어 적이 닿으면 2만큼 라이프가 닳는다.
	}
	else
	{
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"  ";//미사일이 지나간 자리는 " " 로 출력

		SetPositionY(GetPositionY() - 1);//미사일은 이 얻은 Y좌표보다 -1 이면 미사일 출력
		gotoxy(GetPositionX(), GetPositionY());
		cout<<"♡";
	}
}

void CTank::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CTank::CheckColor(int color)
{
	if (color == 1)
	{
		return 4;
	}
	else if (color == 2)
	{
		return 2;
	}
	else if (color == 3)
	{
		return 2;
	}
		else if (color == 4)
	{
		return 2;
	}
		else if (color == 5)
	{
		return 2;
		}

}