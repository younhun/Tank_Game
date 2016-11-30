#pragma once
#include "YH_boss.h"
#include "YH_board.h"
#include "YH_object.h"
#include "YH_tank.h"
#include "YH_enemy.h"
#include "YH_wall.h"
#include "YH_item.h"
#include "YH_over.h"

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setCursortype(CURSOR_TYPE);//Ŀ�� �Ⱥ��̰� ���̴� �Լ�

class CGame
{
public:
	CGame();//�ʱ�ȭ
	void Run();//���ο��� ���� ���� �Լ�
private:
	void GameStart();//���� ����=>Ű���� �Է��� ������ �����Ű���� �Ǿ��ִ�.
	void NextStage();//���� �ܰ�

	void MapSetting();//�� ���� => ���� ����� �� ���� �� ��ũ�� ��� �Ǿ��ְ� �Ѵ�.
	void GameSetting();//���� ����=>�� �������� ������ ���� ���� ��ҵ��� �ʱ�ȭ(clear) �Ѵ�.

	void Makewall_a(const int x, const int y);//�� ����� �Լ� =>���� 2���������� �ִ�.
	void Makewall(const int x, const int y);

	void itemdrop();//������ ���� ���� �Լ�

	int KeyInput();//Ű���� �Է� �Լ�

	void TMtoenemy();//��ũ �̻��ϰ� �� �浹
	void TMtowall();//��ũ �̻��ϰ� �� �浹
	void TMtoboss();//��ũ �̻��ϰ� ���� �浹
	void IMtowall();//�� �̻��ϰ� �� �浹
	void lMtowall_a();//�� �̻��ϰ� �� �浹
	void IMtoTank();//�� �̻��ϰ� ��ũ �浹
	void enemyToTank();//���� ��ũ �浹
	void enemyTowall();//���� �� �浹
	void UMtowall();//���� �̻��ϰ� �� �浹
	void UMtoTank();//���� �̻��ϰ� ��ũ �浹
	void ItemTowall();//�����۰� �� �浹
	void ItemToTank();//�����۰� ��ũ �浹
	
	void IsCollision();//���� �浹�� �����Ű�� ���� ���⿡ ��Ƶд�.

	void gotoxy(int x, int y);
	void SetColor(int color);
	
	void Makeenemy();//������
	void MoveenemyRight();//�� ������ �̵���Ų��
	void MoveenemyLeft();//�� ���� �̵���Ų��
	void Moveenemy();//���� �̵���Ų��(���� ����)
	void Removeenemy();//�� ����
	void MakeTankMissile();//��ũ �̻��� �����.
	void MoveTankMissile();//��ũ �̻��� �̵���Ų��.
	void MakeenemyMissile();//�� �̻��� �����.
	void MoveenemyMissile();//�� �̻��� �̵���Ų��.
	void MakebossMissile();//���� �̻��� �����.
	void MovebossMissile();//���� �̻��� �̵�����Ų��.
	
	void GetScore();//���� ����

	int itemValue;
	int stage;
	
	bool moveLeftAvail;//������ ������
	bool moveRightAvail;//��������
	
	CEnemy &RandomPos(CEnemy &enemy_);//���� �������� �����ϱ�����

	CBoss boss_;//�������� �ٸ� Ŭ���� �ҷ���
	CTank tank_;//�������� �ٸ� Ŭ���� �ҷ���
	
	//���� �迭ó�� ���δ�. �ڱ� ������� �ø��ų� �� �� �ִ�.
	vector<CWall> v_wall_;
	vector<CWall_a> v_wall_a_;
	vector<CEnemy> v_enemy_;
	vector<CTank> v_tankMissile_;
	vector<CEnemy> v_enemyMissile_;
	vector<CBoss> v_bossMissile_;
	vector<CObject> v_object_;	
};
