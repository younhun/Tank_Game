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
void setCursortype(CURSOR_TYPE);//커서 안보이게 쓰이는 함수

class CGame
{
public:
	CGame();//초기화
	void Run();//메인에서 게임 실행 함수
private:
	void GameStart();//게임 시작=>키보드 입력이 있을시 실행시키도록 되어있다.
	void NextStage();//다음 단계

	void MapSetting();//맵 세팅 => 게임 실행시 판 보스 벽 탱크가 출력 되어있게 한다.
	void GameSetting();//게임 세팅=>한 스테이지 종료후 게임 세팅 요소들을 초기화(clear) 한다.

	void Makewall_a(const int x, const int y);//벽 만드는 함수 =>벽은 2가지종류가 있다.
	void Makewall(const int x, const int y);

	void itemdrop();//아이템 떨어 지는 함수

	int KeyInput();//키보드 입력 함수

	void TMtoenemy();//탱크 미사일과 적 충돌
	void TMtowall();//탱크 미사일과 벽 충돌
	void TMtoboss();//탱크 미사일과 보스 충돌
	void IMtowall();//적 미사일과 벽 충돌
	void lMtowall_a();//적 미사일과 벽 충돌
	void IMtoTank();//적 미사일과 탱크 충돌
	void enemyToTank();//적과 탱크 충돌
	void enemyTowall();//적과 벽 충돌
	void UMtowall();//보스 미사일과 벽 충돌
	void UMtoTank();//보스 미사일과 탱크 충돌
	void ItemTowall();//아이템과 벽 충돌
	void ItemToTank();//아이템과 탱크 충돌
	
	void IsCollision();//위의 충돌을 실행시키기 위해 여기에 모아둔다.

	void gotoxy(int x, int y);
	void SetColor(int color);
	
	void Makeenemy();//적생산
	void MoveenemyRight();//적 오른쪽 이동시킨다
	void MoveenemyLeft();//적 왼쪽 이동시킨다
	void Moveenemy();//적을 이동시킨다(보스 포함)
	void Removeenemy();//적 제거
	void MakeTankMissile();//탱크 미사일 만든다.
	void MoveTankMissile();//탱크 미사일 이동시킨다.
	void MakeenemyMissile();//적 미사일 만든다.
	void MoveenemyMissile();//적 미사일 이동시킨다.
	void MakebossMissile();//보스 미사일 만든다.
	void MovebossMissile();//보스 미사일 이동ㅇ시킨다.
	
	void GetScore();//얻은 점수

	int itemValue;
	int stage;
	
	bool moveLeftAvail;//왼쪽이 참인지
	bool moveRightAvail;//거짓인지
	
	CEnemy &RandomPos(CEnemy &enemy_);//적을 랜덤으로 생산하기위함

	CBoss boss_;//정적으로 다른 클래스 불러옴
	CTank tank_;//정적으로 다른 클래스 불러옴
	
	//백터 배열처럼 쓰인다. 자기 마음대로 늘리거나 할 수 있다.
	vector<CWall> v_wall_;
	vector<CWall_a> v_wall_a_;
	vector<CEnemy> v_enemy_;
	vector<CTank> v_tankMissile_;
	vector<CEnemy> v_enemyMissile_;
	vector<CBoss> v_bossMissile_;
	vector<CObject> v_object_;	
};
