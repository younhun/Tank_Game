#include "YH_game.h"

static int gameScore;//게임 점수

CGame::CGame():itemValue(0){}//아이템 값 초기화

void CGame::gotoxy(int x, int y)
{ 
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CGame::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CGame::Run()//메인에서 쓰이는 실행함수
{
	stage = 1;//스테이지는 1부터
	gameScore = 0;//점수는 0점 부터
	system("mode con:cols=57 lines=35");//콘솔 시작위치windows.h. 오른쪽으로 57만큼 아래 줄 35만큼 콘솔창 생성 그리고 옆에 스크롤바 없앤다.
	srand(time(NULL));//시간마다 랜덤 시드 배정
	moveLeftAvail = false;
	moveRightAvail = true;
	GameSetting();//게임 세팅 함수 불러온다.
	MapSetting();//맵 세팅 함수 불러온다.
	while(1) // 키보드의 입력이 있는 지 확인
	{
		if (kbhit())
		{
			KeyInput();
		}
	}
}
void CGame::GameStart()
{
	while(1)//키보드 입력이있는지 확인
	{
		if (kbhit())
		{
			KeyInput();
		}
		else
		{
		    IsCollision();
			GetScore();
			MoveTankMissile();
			Moveenemy();
			MakeenemyMissile();
			MoveenemyMissile();
			MakebossMissile();
			MovebossMissile();
			itemdrop();
			Sleep(100);//0.1초 마다 반응 숫자를 늘리면 게임이 느려진다.
		}
	}
}

int CGame::KeyInput()//키보드 입력 세팅
{
	char input = getch();//입력된 내용이 있으면 첫번째 키코드를 읽어온다. =>Run()함수에 입력이 있나없다 확인했다. 그럼 이함수 실행.
	switch(input)
	{
	case 75:
		tank_.MoveLeft();//탱크의 왼쪽 움직임 함수 실행 방향키 왼쪽
		break; 
	case 77:
		tank_.MoveRight();//탱크의 오른쪽 움직임 함수 실행 방향기 오른쪽
		break;
	case '5':
		for (int i = 0; i < 5; i++)
		{
			Makeenemy();//개임 실행시 적 5개 만든다 이 함수의 내부는 배열
		}
		GameStart();//'5'번시 게임 시작 함수 불러온다.
		break;
	case '2' :
		NextStage();//'2'번누르면 다음스테이지 넘어가는 핵을 만들었다.
		break;
	case ' ':
		MakeTankMissile();//스페이스바 누를시 탱크 미사일 발사 함수 부른다.
		break;
	}
	return 0;
}
void CGame::GameSetting()//한 스테이지 종료후 게임 새팅한다.//clear() 모든 원소 제거 빈 컨테이너로 만든다.
{   
	system("cls");//화면 깨끗이한다.
	v_enemy_.clear();//적 원소 제거
	v_wall_.clear();//벽 원소 제거
	v_wall_a_.clear();
	v_tankMissile_.clear();//탱크 미사일 원소 제거
	v_bossMissile_.clear();//보스 미사일 원소 제거
	v_enemyMissile_.clear();//적 미사일 원소 제거
}//탱크와 보스와 하나이다 배열개념이 아니여서 하지 않는다.

void CGame::MapSetting()//실행 기켯을시 맵 세팅 함수
{	
	CBoard board_;//CBoard 클래스 정적 할당

	board_.BPrint(); // 판 출력

	boss_.SetRandVariable(30);//보스 미사일 발사 간격=> 숫자가 클수록 발사 간격이 길다.
	boss_.SetPositionX(24);//보스 x 좌표 위치
	boss_.SetPositionY(0);//보스 y 좌표 위치
    boss_.Print();//보스 출력

	Makewall(5, 25);
	Makewall_a(15, 23);
	Makewall(25, 25);
	Makewall_a(35, 23);
	Makewall(45, 25);
	//벽 위치 => 밑에 Makewall 함수 정의 해 준다.

	for (int i = 0; i < v_wall_.size(); i++)
	{//백터쓰인다. 벽의 실제 원소 개수를 반환 개수만큼 벽 만든다.
		v_wall_[i].Print();//벽 출력
	}
	
	for (int i = 0; i < v_wall_a_.size(); i++)
	{//백터쓰인다. 벽의 실제 원소 개수를 반환 개수만큼 벽 만든다.
		v_wall_a_[i].Print();//벽 출력
	}

	tank_.SetLife(2);//탱크 라이프 2 정의
	tank_.SetPositionX(26);//탱크 x 좌표 위치
	tank_.SetPositionY(29);//탱크 y 좌표 위치
	tank_.Print();//탱크 출력
}

void CGame::NextStage()//다음 단계
{
	COver over_;//COver 클래스 불러와 정적 할당
	
	if (stage == 6)
	{
		over_.GameOver();//스테이지가 6 이면 종료
	}

	boss_.SetLife(5);//다음 스테이지보스 라이프 5로 받는다.
	system("cls");//한스테이지 종료되면 화면 지우고
	cout<<"♥Next Level !!!♥";//출력
	stage++;//스테이지 하나씩 증가
	gameScore += boss_.GetScore();//게임 점수는 보스로부터 얻은 점수
	gotoxy(12, 12);
	cout<<"Stage :     "<<stage;
	gotoxy(12, 13);
	cout<<"                 ";
	gotoxy(12, 13);
	cout<<"Score :     "<< gameScore;
	//다음 스테이지 넘어가기전 점수와 스테이지 출력한다.

	Sleep(3000);//다음 스테이지 넘어가는 속도
	getch();//입력받으면
	GameSetting();//유닛들 세팅=> 초기화하고
	MapSetting();//맵새팅=>다시 만든다.
	
	for(int i = 0; i < stage * 5; i++)//다음 스테이지는 적이 더 늘어 난다.
	{
		Makeenemy();//스테이지 증가할떄마다 적 생성
	}
	GameStart();//게임 시작
}

void CGame::Makewall(int x, int y)//벽 만들기
{
	CWall wall_;//정적할당

	wall_.SetPositionX(x);//x에 x 좌표 설정
	wall_.SetPositionY(y);//y에 y 좌표 설정
	v_wall_.push_back(wall_);
	//()안에 있는 데이터 추가해서 벽 사이즈 정의할때 v_wall_(배열)로 쓰인다 =>끝부분 복사본 추가한다.
}

void CGame::Makewall_a(int x, int y)//벽 만들기
{
	CWall_a wall_a;

	wall_a.SetPositionX(x);
	wall_a.SetPositionY(y);
	v_wall_a_.push_back(wall_a);
}

void CGame::Makeenemy()//적 만든다.
{
	CEnemy enemy_;
	
	enemy_.SetRandVariable(rand() % 10 + 15);//미사일 랜덤으로 생성 숫자가 작을수록 발사 간격이 짧다.// 15~24
	v_enemy_.push_back(RandomPos(enemy_));//마지막 원소를 추가=>적 랜덤위치를 적 배열로 추가한다.
}

void CGame::MoveTankMissile()//탱크 미사일 이동
{
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{//탱크 미사일도 배열형태이다.
		if (v_tankMissile_[i].GetLife() == 0)//탱크의 미사일 life가 0 즉 위쪽 끝에 닿앟다.
		{
			v_tankMissile_.erase(v_tankMissile_.begin() + i);//i 번째 미사일을 가리키는 반복자를 반환하여 지운다.=>위쪽 끝에 닿으면 없어지게
		}
		else
		{
			v_tankMissile_[i].ShootMissile();//아니면 미사일 발사 위쪽 끝에 닿지 않았다는 뜻
		}
	}
}

void CGame::MakeTankMissile()//탱크 미사일 생성
{
	CTank tankMissile_;//정적할당

	tankMissile_.SetPositionX(tank_.GetPositionX() + 1);//탱크의 X좌표에서 +1 한곳이 미사일 발사 X위치=>탱크 크기에 따른 +!이다.(탱크 가운데서 나가게)
	tankMissile_.SetPositionY(tank_.GetPositionY() - 1);//탱크의 Y좌표 +1 -> 탱크 위치보다 +1에서발사
	v_tankMissile_.push_back(tankMissile_);//미사일을 추가하여 반환=>배열형태로 쓰기위해
}
void CGame::Moveenemy()//적 이동(보스 포함)
{
	int randVar = rand() % 10;//0~9 랜덤 
	
	if (randVar == 0)//보스 랜덤중 0 이면 왼쪽
	{
		boss_.MoveLeft();
	}
	else if (randVar == 1)//보스 랜덤중 1 이면 오른쪽
	{
		boss_.MoveRight();
	}//즉 보스는 한칸씩 좌,우로 이동하는게 아니라 그 위치에있다가 랜덤 숫자가 걸리면 좌혹은 우로 움직인다.

	if (moveRightAvail)//참이면 위에서 참이라고 정함
	{
		MoveenemyRight();//오늘쪽 움직인다.
	}
	else//거짓이면
	{
		MoveenemyLeft();//왼쪽 움직인다.
	}
}

void CGame::MoveenemyRight()//적 오른쪽 이동
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetPositionX() >= 49)//적이 movedown 좌표 알려준다 이게 30이면 x가 30좌표에 아래로 떨어진다.
		{
			moveRightAvail = false;//거짓 즉 오른쪽으로 움직이지 않는다. 49보다 크거나 같게 되면 즉 아래로 움직인다.
		}
	}
	if (moveRightAvail)//참이면 아래 실행
	{
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveRight();//참이면 오른쪽으로 움직인다.
			v_enemy_[i].Print();//적 출력
		}
	}
	else//거짓이면.아래 실행
	{
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveDown();//아래로 움직인다. 거짓이면 오른쪽으로 움직이지않는다. 즉 아래로 내려가서 왼쪽 움직이는거 실행해야한다.
			v_enemy_[i].Print();//적 풀력
		}
		moveLeftAvail = true;//아래로 내려간뒤 왼쪽 움직임.
	}
}

void CGame::MoveenemyLeft()//적 왼쪽 움직임
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetPositionX() <= 1)//왼쪽으로 갈수있는 최대치이다. 이 숫자가 5 이면 x 5좌표 에서 아래로 내려간다.
		{
			moveLeftAvail = false;//거짓이다.왼쪽으로 움직이지 않는다.
		}
	}
	if (moveLeftAvail)//참이면 왼쪽으로 움직인다.
	{
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveLeft();////true 이니 왼쪽으로 움직인다. 움직일떄마다 적 생성
			v_enemy_[i].Print();//적 출력
		}
	}
	else
	{	//거짓이면
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveDown();//왼쪽에서 한칸 내려가게 된다. 그다음 오른쪽으로 움직인다.
			v_enemy_[i].Print();//적 출력
		}
		moveRightAvail = true;//왼쪽에서 한칸 내려가게 된다. 그다음 오른쪽으로 움직인다.
	}
}

void CGame::Removeenemy()//적 제
{
	if (v_enemy_.size() == 0)
	{	
	}
	else
	{
		gotoxy(v_enemy_.back().GetPositionX(), v_enemy_.back().GetPositionY());//back() : 마지막 원소 반환( 원소가 있는지 검사 하지 않는다.)
		cout<<"     ";
		v_enemy_.pop_back();//마지막 원소 삭제 ..제거된 원소는 반환하지 않는다.
	}//적이 삭재되면 그 X와 Y 좌표로 반환하여 "   "빈칸으로 출력
}

void CGame::MakeenemyMissile()//적 미사일 만든다.
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		v_enemy_[i].SetShootVariable(v_enemy_[i].GetShootVariable() + 1);//GetShootVariable 에 +1을 해준것을 SetShootVariable으로 지정한다. 더해준 숫자가 클수록 더 많은 미사일이 나아간다.
		if (v_enemy_[i].GetRandVariable() == v_enemy_[i].GetShootVariable())//정해준 shootvariable와 랜덤 미사일 발사가 같으면 발사된다.
		{	
			CEnemy Missile_;
			Missile_.SetPositionX(v_enemy_[i].GetPositionX() + 3);//적 x축 방향 +3 에서 미사일이 나간다.=> 적 가운데에서 미사일이 나간다. 
			Missile_.SetPositionY(v_enemy_[i].GetPositionY() + 1);//미사일은 적 위치에서 y축 +1 방향으로 부터 나간다.
			v_enemyMissile_.push_back(Missile_);//마지막 원소를 반환한다.

			v_enemy_[i].SetShootVariable(0);//초기화
		}
	}
}

void CGame::MoveenemyMissile()//적미사일 움직임
{
	for (int i = 0; i < v_enemyMissile_.size(); i++)
	{
		if (v_enemyMissile_[i].GetLife() == 0)//미사일이 라이프가 0으로 얻는다 => 맨끝에닿으면
		{
			v_enemyMissile_.erase(v_enemyMissile_.begin() + i);//begin i번째 원소를 가리는 랜덤 엑세스 반복자 erase : 반복자 원소를 제거한다.=> 맨끝 미사일 지운다. 지운자리를 enemy.c 에서 ' ' 로 표시
		}
		else
		{
			v_enemyMissile_[i].ShootMissile();//라이프가 0이아니면 미사일 발사.
		}
	}
}
void CGame::MakebossMissile()
{
	boss_.SetShootVariable(boss_.GetShootVariable() + 1);
	if (boss_.GetRandVariable() == boss_.GetShootVariable())
	{
		CBoss Missile;
		Missile.SetPositionX(boss_.GetPositionX() + 3);//보스 x축 방향 +3 에서 미사일이 나간다.=> 보스 가운데에서 미사일이 나간다.
		Missile.SetPositionY(boss_.GetPositionY() + 1);//미사일은 보스 위치에서 y축 +1 방향으로 부터 나간다.
		v_bossMissile_.push_back(Missile);//마지막 원소를 반환한다.

		boss_.SetShootVariable(0);//초기화
	}
}
void CGame::MovebossMissile()
{
	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		if (v_bossMissile_[i].GetLife() == 0)//끝에 닿는다 이것을 라이프 0 이라고 지정해놨었다.
		{
			v_bossMissile_.erase(v_bossMissile_.begin() + i);//begin i번째 원소를 가리는 반복자 지운다 => 맨끝 미사일 지운다. 지운자리를 boss.c 에서 ' ' 로 표시
		}
		else
		{
			v_bossMissile_[i].ShootMissile();//라이프가 0이아니면 미사일 발사.
		}
	}
}

void CGame::IsCollision()//접촉 할 경우 불러온다.
{
	TMtowall();//탱크 미사일이 벽에 닿을떄
	TMtoenemy();//탱크 미사일이 적에 닿을때
	IMtoTank();//적미사일이 탱크에게 닿을떄
	IMtowall();//적 미사일이 벽에 닿을때
	enemyTowall();//적이 벽에 닿을떄
	UMtoTank();//보스 미사일이 탱크에 닿을떄
	UMtowall();//보스 미사일이 벽에 닿을떄
	TMtoboss();//탱크 미사일이 보스에 닿을떄
	enemyToTank();//적이 탱크에 닿을떄
	ItemTowall();//아이템이 벽에 닿을떄
	ItemToTank();//아이템이 탱크에 닿을떄
}

CEnemy &CGame::RandomPos(CEnemy &enemy_)//적 랜덤 위치 생성
{
	bool _isPossible = false;
	int randX = 0, randY = 0, checkCount = 0;//초기화
	
	if (v_enemy_.size() == 0)//적 원소 없다
	{
		randX = rand() % 35 + 10;//x 10~44 중 무작위
		randY = rand() % 19 + 5;//y 1~19 중 무작위

		enemy_.SetPositionX(randX);//무작위 X를 적 X위치에 지정
		enemy_.SetPositionY(randY);//무작위 Y를 적 Y위치에 지정
	}
	else
	{
		while(!_isPossible)//거짓이면 다시 참이된다.
		{
			randX = rand() % 35 + 10;
			randY = rand() % 19 + 1;
			
			_isPossible = true;
		}
		enemy_.SetPositionX(randX);
		enemy_.SetPositionY(randY);
	}
	enemy_.Print();//적 출력

	return enemy_;//반환
}

void CGame::GetScore()//점수 획득
{

	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetLife() <= 0)//적 라이프가 0과같거나 작을떄
		{
			gameScore += v_enemy_[i].GetScore();//적을 처치한만큼 점수가 올라 간다.
			gotoxy(22, 32);
			cout<<"            ";
			gotoxy(22, 32);
			cout<<"Score :     "<<gameScore;
			//여기 좌표에서 점수가 올라가는걸 볼수 있다.
			gotoxy(v_enemy_[i].GetPositionX(), v_enemy_[i].GetPositionY());
			cout<<"     ";//적 라이프가 0 이면 "   "빈칸으로
			v_enemy_.erase(v_enemy_.begin() + i);//i 번째 원소 반환하여 지운다.
		}
	}
}
void CGame::IMtoTank()//적미사일이 탱크에 적중
{	
	COver over_;

	for (int i = 0; i < v_enemyMissile_.size(); i++)//적 미사일
	{
		if ((v_enemyMissile_[i].GetPositionY() == 29) &&//적 미사일이 탱크 위치의 y 좌표 같다.
			((v_enemyMissile_[i].GetPositionX() - tank_.GetPositionX() >= 0) &&
			(v_enemyMissile_[i].GetPositionX() - tank_.GetPositionX() < 4)))
		{	//위에 4보다 작다를 더크게하면 탱크에 맞지안아도 미사일에 맞는것 처럼 된다. =>탱크의 크기를 고려해서 만든거다.
			tank_.SetLife(tank_.GetLife() - 1);// 탱크의 라이프는 지금 라이프보다 -1 된다.
			v_enemyMissile_[i].SetLife(0);//미사일은 사라진다. 위에서 정의했다.
			if (tank_.GetLife() == 0)// 탱크 라이프가 0이면
			{
				over_.GameOver();//게임 종료
			}
		}
	}
}

void CGame::TMtowall()//탱크 미사일이 벽에 적중
{
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_tankMissile_[i].GetPositionY() == v_wall_[j].GetPositionY() + 1) &&//이렇게 둔 이유는 미사일은 y좌표로 벽과 일정한게 아니라 벽보다 y+1 만큼 접촉되어 맞는것 이다.
				((v_tankMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() >= -1) &&//-1보다 크면 왼쪽 벽부터 탱크 미사일에 맞으면 부서진다. 
				(v_tankMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() < 5)))//5보다 크면 오른쪽 벽부터 탱크 미사일에 맞어도 부서진다.
			{	//탱크미사일 좌표에서 벽 좌표뺀것이 0<= x <5 인이유는 벽의 크기를 고려해서 한것 이다.
				v_tankMissile_[i].SetLife(0);//탱크 미사일이 벽에 닿으면 즉 죽으면
				gotoxy(v_tankMissile_[i].GetPositionX(), v_tankMissile_[i].GetPositionY());
				cout<<"  ";//그 위치에가서 " " 로 출력

			}
		}
	}
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_tankMissile_[i].GetPositionY() == v_wall_a_[j].GetPositionY()+1) &&//이렇게 둔 이유는 미사일은 y좌표로 벽과 일정한게 아니라 벽보다 y+1 만큼 접촉되어 맞는것 이다.
				((v_tankMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= -1) &&//-1보다 크면 왼쪽 벽부터 탱크 미사일에 맞으면 부서진다. 
				(v_tankMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 6)))//6보다 크면 오른쪽 벽부터 탱크 미사일에 맞어도 부서진다.
			
			{	v_tankMissile_[i].SetLife(0);//탱크 미사일이 벽에 닿으면 즉 죽으면
				gotoxy(v_tankMissile_[i].GetPositionX(), v_tankMissile_[i].GetPositionY());
				cout<<" ";//그 위치에가서 " " 로 출력
			}
		}
	}
}

void CGame::TMtoenemy()//탱크 미사일이 적과 부딪침
{
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		for (int j = 0; j < v_enemy_.size(); j++)
		{
			if ((v_tankMissile_[i].GetPositionY() == v_enemy_[j].GetPositionY()) &&//탱크 미사일과 적 y 방향 같다 => 충돌
				((v_tankMissile_[i].GetPositionX() - v_enemy_[j].GetPositionX() >= -1) && 
				(v_tankMissile_[i].GetPositionX() - v_enemy_[j].GetPositionX() < 6)))
			{	//이 범위도 적의 크기를 고려해서 한것이다. 적의 어느 부분을 맞어도 맞는것으로 해야하기에
				v_tankMissile_[i].SetLife(0);//미사일이 적과 닿는다 즉 죽는다.
				v_enemy_[j].SetLife(v_enemy_[j].GetLife() - 1);//적의 생명 -1
			}
		}
	}
}

void CGame::IMtowall()//적미사일이 벽에 맞을시
{
	for (int j = 0; j < v_wall_.size(); j++)
	{
		for (int i = 0; i < v_enemyMissile_.size(); i++)
		{
			if ((v_enemyMissile_[i].GetPositionY() == v_wall_[j].GetPositionY() - 1) &&//적미사일이 벽보다 y로 -1일때 즉 벽에 충돌  y좌표로 벽과 일정한게 아니라 벽보다 y-1 만큼 접촉되어 맞는것 이다.
				((v_enemyMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() >= 0) && 
				(v_enemyMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() < 5)))
			{	//벽 크기에 따른 범위 지정
				
				gotoxy(v_enemyMissile_[i].GetPositionX(), v_enemyMissile_[i].GetPositionY());
				cout<<" ";//벽에 맞은 부분을 " "로 출력 없애준다는 의미
				v_enemyMissile_.erase(v_enemyMissile_.begin() + i);
				//begin i번째 원소를 가리는 랜덤 엑세스 반복자 
				//erase : 반복자 원소를 제거한다.=> 맨끝 미사일 지운다. 지운자리를 enemy.c 에서 ' ' 로 표시
			}	//배열 형식은 다 지워줘야 한다.
		}
	}
	for (int j = 0; j < v_wall_a_.size(); j++)
	{
		for (int i = 0; i < v_enemyMissile_.size(); i++)
		{
			if ((v_enemyMissile_[i].GetPositionY() == v_wall_a_[j].GetPositionY() - 1) &&//적미사일이 벽보다 y로 -1일때 즉 벽에 충돌  y좌표로 벽과 일정한게 아니라 벽보다 y+1 만큼 접촉되어 맞는것 이다.
				((v_enemyMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= 0) && 
				(v_enemyMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 6)))
			{	//벽 크기에 따른 범위 지정
				
				gotoxy(v_enemyMissile_[i].GetPositionX(), v_enemyMissile_[i].GetPositionY());
				cout<<" ";//벽에 맞은 부분을 " "로 출력 없애준다는 의미
				v_enemyMissile_.erase(v_enemyMissile_.begin() + i);
				//begin i번째 원소를 가리는 랜덤 엑세스 반복자 
				//erase : 반복자 원소를 제거한다.=> 맨끝 미사일 지운다. 지운자리를 enemy.c 에서 ' ' 로 표시
			}
		}
	}

}

void CGame::enemyTowall()//적과 벽의 충돌
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_enemy_[i].GetPositionY() == v_wall_[j].GetPositionY())&&//적과 벽이 y 좌표 같다.
				((v_enemy_[i].GetPositionX() == v_wall_[j].GetPositionX() + 2)))//적과 벽의 x 같다. 크기를 고려한 +2 이다.
			{
				gotoxy(v_wall_[j].GetPositionX(), v_wall_[j].GetPositionY());//적과 벽이 부딪히면 벽은 없어진다.
				cout<<"     ";//빈칸 출력
				v_wall_.erase(v_wall_.begin() + j);
				//벽의 j 번째 가리켜 지운다.
			}
		}
	}
for (int i = 0; i < v_enemy_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_enemy_[i].GetPositionY() == v_wall_a_[j].GetPositionY())&&//적과 벽이 y 좌표 같다.
				((v_enemy_[i].GetPositionX() == v_wall_a_[j].GetPositionX() + 2)))//적과 벽의 x 같다. 크기를 고려한 +2 이다.
			{
				gotoxy(v_wall_a_[j].GetPositionX(), v_wall_a_[j].GetPositionY());//적과 벽이 부딪히면 벽은 없어진다.
				cout<<"     ";//빈칸 출력
				v_wall_a_.erase(v_wall_a_.begin() + j);
				//벽의 j 번째 가리켜 지운다.
			}
		}
	}
}

void CGame::UMtoTank()//보스 미사일과 탱크의 충돌
{
	COver over_;
	CGame game_;

	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		if ((v_bossMissile_[i].GetPositionY() == 29) &&//보스 미사일이 탱크 위치 y 같다.
			((v_bossMissile_[i].GetPositionX() - tank_.GetPositionX() >= 0) && 
				(v_bossMissile_[i].GetPositionX() - tank_.GetPositionX() < 4)))
		{		//탱크 크기에 따른 범위 조절
				over_.GameOver();//게임 종료 erase 할것없이 종료 된다.
		}
	}
}

void CGame::UMtowall()//보스 미사일 벽과 충돌
{
	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_bossMissile_[i].GetPositionY() == v_wall_[j].GetPositionY() - 1) &&//충돌 y 좌표 -1 이여야한다. 부딪치는것이기 때문데
				((v_bossMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() >= 0) &&
				(v_bossMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() < 5)))
			{	//벽의 크기에 따른 범위 조절
				v_bossMissile_[i].SetLife(0);//보스 미사일 소멸된다.
				gotoxy(v_bossMissile_[i].GetPositionX(), v_bossMissile_[i].GetPositionY());
				cout<<" ";
			}
		}
	}
	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_bossMissile_[i].GetPositionY() == v_wall_a_[j].GetPositionY() - 1) &&//충돌 y 좌표 -1 이여야한다. 부딪치는것이기 때문데
				((v_bossMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= 0) &&
				(v_bossMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 6)))
			{	//벽의 크기에 따른 범위 조절
				v_bossMissile_[i].SetLife(0);//보스 미사일 소멸된다.
				gotoxy(v_bossMissile_[i].GetPositionX(), v_bossMissile_[i].GetPositionY());
				cout<<" ";
			}
		}
	}
}
void CGame::TMtoboss()//탱크 미사일 보스 맞춤
{
	CGame game_;
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		if ((v_tankMissile_[i].GetPositionY() == 0) &&//보스와 미사일 충돌
			((v_tankMissile_[i].GetPositionX() - boss_.GetPositionX() >= 0) &&
			(v_tankMissile_[i].GetPositionX() - boss_.GetPositionX() < 5)))
		{	//크기에 따른 범위
			boss_.SetLife(boss_.GetLife() - 1);//미사일 맞으면 보스 라이프 1개 소멸
		}
		if (boss_.GetLife() == 0)//보스라이프 0 이면
		{
			NextStage();//다음 스테이지
		}
	}
}

void CGame::enemyToTank()//적이 탱크와 충돌
{
	COver over_;
	CGame game_;
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetPositionY() == 29)//탱크 위치
		{
			over_.GameOver();//게임 종료
		}
	}
}

void CGame::ItemTowall()//아이템과 벽 충돌
{
	for (int i = 0; i < v_object_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_object_[i].GetPositionY() == v_wall_[j].GetPositionY() - 1) &&//충돌
				((v_object_[i].GetPositionX() - v_wall_[j].GetPositionX() >= -2) &&
				(v_object_[i].GetPositionX() - v_wall_[j].GetPositionX() < 6)))
			{	//크기에 따른 범위 조절
				v_object_[i].SetLife(0);//소멸된다.
				gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
				cout<<"     ";
			}
		}
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetLife() == 0)
		{
			v_object_.erase(v_object_.begin() + i);//i 만큼 반환하여 지운다
		}
	}

	for (int i = 0; i < v_object_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_object_[i].GetPositionY() == v_wall_a_[j].GetPositionY() - 1) &&//충돌
				((v_object_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= -2) &&
				(v_object_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 5)))
			{	//크기에 따른 범위 조절
				v_object_[i].SetLife(0);//소멸된다.
				gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
				cout<<"     ";
			}
		}
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetLife() == 0)//소멸될시
		{
			v_object_.erase(v_object_.begin() + i);//i 만큼 반환하여 지운다
		}
	}
}

void CGame::ItemToTank()//아이템이 탱크에 닿을떄
{	
	for (int i = 0; i < v_object_.size(); i++)
	{
		if ((v_object_[i].GetPositionY() == 29) &&//탱크 위치에 간다.
			((v_object_[i].GetPositionX() - tank_.GetPositionX() >= 0) &&
			(v_object_[i].GetPositionX() - tank_.GetPositionX() < 3)))
		{	//크기에 따른 범위
			v_object_[i].SetLife(0);//닿아서 소멸된다.
			gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
			cout<<"   ";//" " 로 출력
			tank_.SetLife(tank_.GetLife() + 1);//탱크 라이프 1증가
		}
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetLife() == 0)
		{
			v_object_.erase(v_object_.begin() + i);//i 만큼 반환하여 지운다
		}
	}
	gotoxy(38, 32);
	cout<<"                     ";
	gotoxy(38, 32);
	for (int i = 1; i < tank_.GetLife(); i++)//탱크 라이프가 증가할때 => 템 먹었을떄
	{
		if (i == 1)
		{
			SetColor(15);
		}
		else if (i ==2)
		{
			SetColor(15);
		}
		else if (i == 3)
		{
			SetColor(15);
		}else if(i == 4)
		{
			SetColor(15);
		}else if(i == 5)
		{
			SetColor(15);
		}
		printf("[凸]");
	}

	SetColor(7);
}

void CGame::itemdrop()
{
	CItem item_;

	itemValue++;
	if (itemValue == 200)//100이면 아이템 떨어지는 간격이 더 좁다.
	{	
		CObject object_;
		object_.SetPositionX(rand() % 51);//X축 0~50 무작위 위치결정 판의 가로축 일부
		object_.SetPositionY(0);//Y축 0
		v_object_.push_back(object_);// 반환한다.
		itemValue = 0;//다시 초기화
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetPositionY() < 29)//Y축 29보다 작으면
		{
			gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());//지정위치에는 ' ' 공백
			cout<<"    ";
			v_object_[i].SetPositionY(v_object_[i].GetPositionY() + 1);// 지정위치보다 Y 가 +1이면 아이템 모양 출력
			gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
			item_.Print();
		}
	}
}