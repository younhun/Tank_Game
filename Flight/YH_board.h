#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class CBoard{
public:
	CBoard();//�ʱ�ȭ
	void BPrint();//�� �׸���
private:
	void gotoxy(int x, int y);
	int stage;//��������
	int gameScore;//���� ����
};
