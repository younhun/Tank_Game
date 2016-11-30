#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class CBoard{
public:
	CBoard();//초기화
	void BPrint();//판 그리기
private:
	void gotoxy(int x, int y);
	int stage;//스테이지
	int gameScore;//게임 점수
};
