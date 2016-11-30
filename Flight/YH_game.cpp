#include "YH_game.h"

static int gameScore;//���� ����

CGame::CGame():itemValue(0){}//������ �� �ʱ�ȭ

void CGame::gotoxy(int x, int y)
{ 
	COORD position = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CGame::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CGame::Run()//���ο��� ���̴� �����Լ�
{
	stage = 1;//���������� 1����
	gameScore = 0;//������ 0�� ����
	system("mode con:cols=57 lines=35");//�ܼ� ������ġwindows.h. ���������� 57��ŭ �Ʒ� �� 35��ŭ �ܼ�â ���� �׸��� ���� ��ũ�ѹ� ���ش�.
	srand(time(NULL));//�ð����� ���� �õ� ����
	moveLeftAvail = false;
	moveRightAvail = true;
	GameSetting();//���� ���� �Լ� �ҷ��´�.
	MapSetting();//�� ���� �Լ� �ҷ��´�.
	while(1) // Ű������ �Է��� �ִ� �� Ȯ��
	{
		if (kbhit())
		{
			KeyInput();
		}
	}
}
void CGame::GameStart()
{
	while(1)//Ű���� �Է����ִ��� Ȯ��
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
			Sleep(100);//0.1�� ���� ���� ���ڸ� �ø��� ������ ��������.
		}
	}
}

int CGame::KeyInput()//Ű���� �Է� ����
{
	char input = getch();//�Էµ� ������ ������ ù��° Ű�ڵ带 �о�´�. =>Run()�Լ��� �Է��� �ֳ����� Ȯ���ߴ�. �׷� ���Լ� ����.
	switch(input)
	{
	case 75:
		tank_.MoveLeft();//��ũ�� ���� ������ �Լ� ���� ����Ű ����
		break; 
	case 77:
		tank_.MoveRight();//��ũ�� ������ ������ �Լ� ���� ����� ������
		break;
	case '5':
		for (int i = 0; i < 5; i++)
		{
			Makeenemy();//���� ����� �� 5�� ����� �� �Լ��� ���δ� �迭
		}
		GameStart();//'5'���� ���� ���� �Լ� �ҷ��´�.
		break;
	case '2' :
		NextStage();//'2'�������� ������������ �Ѿ�� ���� �������.
		break;
	case ' ':
		MakeTankMissile();//�����̽��� ������ ��ũ �̻��� �߻� �Լ� �θ���.
		break;
	}
	return 0;
}
void CGame::GameSetting()//�� �������� ������ ���� �����Ѵ�.//clear() ��� ���� ���� �� �����̳ʷ� �����.
{   
	system("cls");//ȭ�� �������Ѵ�.
	v_enemy_.clear();//�� ���� ����
	v_wall_.clear();//�� ���� ����
	v_wall_a_.clear();
	v_tankMissile_.clear();//��ũ �̻��� ���� ����
	v_bossMissile_.clear();//���� �̻��� ���� ����
	v_enemyMissile_.clear();//�� �̻��� ���� ����
}//��ũ�� ������ �ϳ��̴� �迭������ �ƴϿ��� ���� �ʴ´�.

void CGame::MapSetting()//���� �������� �� ���� �Լ�
{	
	CBoard board_;//CBoard Ŭ���� ���� �Ҵ�

	board_.BPrint(); // �� ���

	boss_.SetRandVariable(30);//���� �̻��� �߻� ����=> ���ڰ� Ŭ���� �߻� ������ ���.
	boss_.SetPositionX(24);//���� x ��ǥ ��ġ
	boss_.SetPositionY(0);//���� y ��ǥ ��ġ
    boss_.Print();//���� ���

	Makewall(5, 25);
	Makewall_a(15, 23);
	Makewall(25, 25);
	Makewall_a(35, 23);
	Makewall(45, 25);
	//�� ��ġ => �ؿ� Makewall �Լ� ���� �� �ش�.

	for (int i = 0; i < v_wall_.size(); i++)
	{//���;��δ�. ���� ���� ���� ������ ��ȯ ������ŭ �� �����.
		v_wall_[i].Print();//�� ���
	}
	
	for (int i = 0; i < v_wall_a_.size(); i++)
	{//���;��δ�. ���� ���� ���� ������ ��ȯ ������ŭ �� �����.
		v_wall_a_[i].Print();//�� ���
	}

	tank_.SetLife(2);//��ũ ������ 2 ����
	tank_.SetPositionX(26);//��ũ x ��ǥ ��ġ
	tank_.SetPositionY(29);//��ũ y ��ǥ ��ġ
	tank_.Print();//��ũ ���
}

void CGame::NextStage()//���� �ܰ�
{
	COver over_;//COver Ŭ���� �ҷ��� ���� �Ҵ�
	
	if (stage == 6)
	{
		over_.GameOver();//���������� 6 �̸� ����
	}

	boss_.SetLife(5);//���� ������������ ������ 5�� �޴´�.
	system("cls");//�ѽ������� ����Ǹ� ȭ�� �����
	cout<<"��Next Level !!!��";//���
	stage++;//�������� �ϳ��� ����
	gameScore += boss_.GetScore();//���� ������ �����κ��� ���� ����
	gotoxy(12, 12);
	cout<<"Stage :     "<<stage;
	gotoxy(12, 13);
	cout<<"                 ";
	gotoxy(12, 13);
	cout<<"Score :     "<< gameScore;
	//���� �������� �Ѿ���� ������ �������� ����Ѵ�.

	Sleep(3000);//���� �������� �Ѿ�� �ӵ�
	getch();//�Է¹�����
	GameSetting();//���ֵ� ����=> �ʱ�ȭ�ϰ�
	MapSetting();//�ʻ���=>�ٽ� �����.
	
	for(int i = 0; i < stage * 5; i++)//���� ���������� ���� �� �þ� ����.
	{
		Makeenemy();//�������� �����ҋ����� �� ����
	}
	GameStart();//���� ����
}

void CGame::Makewall(int x, int y)//�� �����
{
	CWall wall_;//�����Ҵ�

	wall_.SetPositionX(x);//x�� x ��ǥ ����
	wall_.SetPositionY(y);//y�� y ��ǥ ����
	v_wall_.push_back(wall_);
	//()�ȿ� �ִ� ������ �߰��ؼ� �� ������ �����Ҷ� v_wall_(�迭)�� ���δ� =>���κ� ���纻 �߰��Ѵ�.
}

void CGame::Makewall_a(int x, int y)//�� �����
{
	CWall_a wall_a;

	wall_a.SetPositionX(x);
	wall_a.SetPositionY(y);
	v_wall_a_.push_back(wall_a);
}

void CGame::Makeenemy()//�� �����.
{
	CEnemy enemy_;
	
	enemy_.SetRandVariable(rand() % 10 + 15);//�̻��� �������� ���� ���ڰ� �������� �߻� ������ ª��.// 15~24
	v_enemy_.push_back(RandomPos(enemy_));//������ ���Ҹ� �߰�=>�� ������ġ�� �� �迭�� �߰��Ѵ�.
}

void CGame::MoveTankMissile()//��ũ �̻��� �̵�
{
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{//��ũ �̻��ϵ� �迭�����̴�.
		if (v_tankMissile_[i].GetLife() == 0)//��ũ�� �̻��� life�� 0 �� ���� ���� ��۴�.
		{
			v_tankMissile_.erase(v_tankMissile_.begin() + i);//i ��° �̻����� ����Ű�� �ݺ��ڸ� ��ȯ�Ͽ� �����.=>���� ���� ������ ��������
		}
		else
		{
			v_tankMissile_[i].ShootMissile();//�ƴϸ� �̻��� �߻� ���� ���� ���� �ʾҴٴ� ��
		}
	}
}

void CGame::MakeTankMissile()//��ũ �̻��� ����
{
	CTank tankMissile_;//�����Ҵ�

	tankMissile_.SetPositionX(tank_.GetPositionX() + 1);//��ũ�� X��ǥ���� +1 �Ѱ��� �̻��� �߻� X��ġ=>��ũ ũ�⿡ ���� +!�̴�.(��ũ ����� ������)
	tankMissile_.SetPositionY(tank_.GetPositionY() - 1);//��ũ�� Y��ǥ +1 -> ��ũ ��ġ���� +1�����߻�
	v_tankMissile_.push_back(tankMissile_);//�̻����� �߰��Ͽ� ��ȯ=>�迭���·� ��������
}
void CGame::Moveenemy()//�� �̵�(���� ����)
{
	int randVar = rand() % 10;//0~9 ���� 
	
	if (randVar == 0)//���� ������ 0 �̸� ����
	{
		boss_.MoveLeft();
	}
	else if (randVar == 1)//���� ������ 1 �̸� ������
	{
		boss_.MoveRight();
	}//�� ������ ��ĭ�� ��,��� �̵��ϴ°� �ƴ϶� �� ��ġ���ִٰ� ���� ���ڰ� �ɸ��� ��Ȥ�� ��� �����δ�.

	if (moveRightAvail)//���̸� ������ ���̶�� ����
	{
		MoveenemyRight();//������ �����δ�.
	}
	else//�����̸�
	{
		MoveenemyLeft();//���� �����δ�.
	}
}

void CGame::MoveenemyRight()//�� ������ �̵�
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetPositionX() >= 49)//���� movedown ��ǥ �˷��ش� �̰� 30�̸� x�� 30��ǥ�� �Ʒ��� ��������.
		{
			moveRightAvail = false;//���� �� ���������� �������� �ʴ´�. 49���� ũ�ų� ���� �Ǹ� �� �Ʒ��� �����δ�.
		}
	}
	if (moveRightAvail)//���̸� �Ʒ� ����
	{
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveRight();//���̸� ���������� �����δ�.
			v_enemy_[i].Print();//�� ���
		}
	}
	else//�����̸�.�Ʒ� ����
	{
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveDown();//�Ʒ��� �����δ�. �����̸� ���������� ���������ʴ´�. �� �Ʒ��� �������� ���� �����̴°� �����ؾ��Ѵ�.
			v_enemy_[i].Print();//�� Ǯ��
		}
		moveLeftAvail = true;//�Ʒ��� �������� ���� ������.
	}
}

void CGame::MoveenemyLeft()//�� ���� ������
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetPositionX() <= 1)//�������� �����ִ� �ִ�ġ�̴�. �� ���ڰ� 5 �̸� x 5��ǥ ���� �Ʒ��� ��������.
		{
			moveLeftAvail = false;//�����̴�.�������� �������� �ʴ´�.
		}
	}
	if (moveLeftAvail)//���̸� �������� �����δ�.
	{
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveLeft();////true �̴� �������� �����δ�. �����ϋ����� �� ����
			v_enemy_[i].Print();//�� ���
		}
	}
	else
	{	//�����̸�
		for (int i = 0; i < v_enemy_.size(); i++)
		{
			v_enemy_[i].MoveDown();//���ʿ��� ��ĭ �������� �ȴ�. �״��� ���������� �����δ�.
			v_enemy_[i].Print();//�� ���
		}
		moveRightAvail = true;//���ʿ��� ��ĭ �������� �ȴ�. �״��� ���������� �����δ�.
	}
}

void CGame::Removeenemy()//�� ��
{
	if (v_enemy_.size() == 0)
	{	
	}
	else
	{
		gotoxy(v_enemy_.back().GetPositionX(), v_enemy_.back().GetPositionY());//back() : ������ ���� ��ȯ( ���Ұ� �ִ��� �˻� ���� �ʴ´�.)
		cout<<"     ";
		v_enemy_.pop_back();//������ ���� ���� ..���ŵ� ���Ҵ� ��ȯ���� �ʴ´�.
	}//���� ����Ǹ� �� X�� Y ��ǥ�� ��ȯ�Ͽ� "   "��ĭ���� ���
}

void CGame::MakeenemyMissile()//�� �̻��� �����.
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		v_enemy_[i].SetShootVariable(v_enemy_[i].GetShootVariable() + 1);//GetShootVariable �� +1�� ���ذ��� SetShootVariable���� �����Ѵ�. ������ ���ڰ� Ŭ���� �� ���� �̻����� ���ư���.
		if (v_enemy_[i].GetRandVariable() == v_enemy_[i].GetShootVariable())//������ shootvariable�� ���� �̻��� �߻簡 ������ �߻�ȴ�.
		{	
			CEnemy Missile_;
			Missile_.SetPositionX(v_enemy_[i].GetPositionX() + 3);//�� x�� ���� +3 ���� �̻����� ������.=> �� ������� �̻����� ������. 
			Missile_.SetPositionY(v_enemy_[i].GetPositionY() + 1);//�̻����� �� ��ġ���� y�� +1 �������� ���� ������.
			v_enemyMissile_.push_back(Missile_);//������ ���Ҹ� ��ȯ�Ѵ�.

			v_enemy_[i].SetShootVariable(0);//�ʱ�ȭ
		}
	}
}

void CGame::MoveenemyMissile()//���̻��� ������
{
	for (int i = 0; i < v_enemyMissile_.size(); i++)
	{
		if (v_enemyMissile_[i].GetLife() == 0)//�̻����� �������� 0���� ��´� => �ǳ���������
		{
			v_enemyMissile_.erase(v_enemyMissile_.begin() + i);//begin i��° ���Ҹ� ������ ���� ������ �ݺ��� erase : �ݺ��� ���Ҹ� �����Ѵ�.=> �ǳ� �̻��� �����. �����ڸ��� enemy.c ���� ' ' �� ǥ��
		}
		else
		{
			v_enemyMissile_[i].ShootMissile();//�������� 0�̾ƴϸ� �̻��� �߻�.
		}
	}
}
void CGame::MakebossMissile()
{
	boss_.SetShootVariable(boss_.GetShootVariable() + 1);
	if (boss_.GetRandVariable() == boss_.GetShootVariable())
	{
		CBoss Missile;
		Missile.SetPositionX(boss_.GetPositionX() + 3);//���� x�� ���� +3 ���� �̻����� ������.=> ���� ������� �̻����� ������.
		Missile.SetPositionY(boss_.GetPositionY() + 1);//�̻����� ���� ��ġ���� y�� +1 �������� ���� ������.
		v_bossMissile_.push_back(Missile);//������ ���Ҹ� ��ȯ�Ѵ�.

		boss_.SetShootVariable(0);//�ʱ�ȭ
	}
}
void CGame::MovebossMissile()
{
	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		if (v_bossMissile_[i].GetLife() == 0)//���� ��´� �̰��� ������ 0 �̶�� �����س�����.
		{
			v_bossMissile_.erase(v_bossMissile_.begin() + i);//begin i��° ���Ҹ� ������ �ݺ��� ����� => �ǳ� �̻��� �����. �����ڸ��� boss.c ���� ' ' �� ǥ��
		}
		else
		{
			v_bossMissile_[i].ShootMissile();//�������� 0�̾ƴϸ� �̻��� �߻�.
		}
	}
}

void CGame::IsCollision()//���� �� ��� �ҷ��´�.
{
	TMtowall();//��ũ �̻����� ���� ������
	TMtoenemy();//��ũ �̻����� ���� ������
	IMtoTank();//���̻����� ��ũ���� ������
	IMtowall();//�� �̻����� ���� ������
	enemyTowall();//���� ���� ������
	UMtoTank();//���� �̻����� ��ũ�� ������
	UMtowall();//���� �̻����� ���� ������
	TMtoboss();//��ũ �̻����� ������ ������
	enemyToTank();//���� ��ũ�� ������
	ItemTowall();//�������� ���� ������
	ItemToTank();//�������� ��ũ�� ������
}

CEnemy &CGame::RandomPos(CEnemy &enemy_)//�� ���� ��ġ ����
{
	bool _isPossible = false;
	int randX = 0, randY = 0, checkCount = 0;//�ʱ�ȭ
	
	if (v_enemy_.size() == 0)//�� ���� ����
	{
		randX = rand() % 35 + 10;//x 10~44 �� ������
		randY = rand() % 19 + 5;//y 1~19 �� ������

		enemy_.SetPositionX(randX);//������ X�� �� X��ġ�� ����
		enemy_.SetPositionY(randY);//������ Y�� �� Y��ġ�� ����
	}
	else
	{
		while(!_isPossible)//�����̸� �ٽ� ���̵ȴ�.
		{
			randX = rand() % 35 + 10;
			randY = rand() % 19 + 1;
			
			_isPossible = true;
		}
		enemy_.SetPositionX(randX);
		enemy_.SetPositionY(randY);
	}
	enemy_.Print();//�� ���

	return enemy_;//��ȯ
}

void CGame::GetScore()//���� ȹ��
{

	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetLife() <= 0)//�� �������� 0�����ų� ������
		{
			gameScore += v_enemy_[i].GetScore();//���� óġ�Ѹ�ŭ ������ �ö� ����.
			gotoxy(22, 32);
			cout<<"            ";
			gotoxy(22, 32);
			cout<<"Score :     "<<gameScore;
			//���� ��ǥ���� ������ �ö󰡴°� ���� �ִ�.
			gotoxy(v_enemy_[i].GetPositionX(), v_enemy_[i].GetPositionY());
			cout<<"     ";//�� �������� 0 �̸� "   "��ĭ����
			v_enemy_.erase(v_enemy_.begin() + i);//i ��° ���� ��ȯ�Ͽ� �����.
		}
	}
}
void CGame::IMtoTank()//���̻����� ��ũ�� ����
{	
	COver over_;

	for (int i = 0; i < v_enemyMissile_.size(); i++)//�� �̻���
	{
		if ((v_enemyMissile_[i].GetPositionY() == 29) &&//�� �̻����� ��ũ ��ġ�� y ��ǥ ����.
			((v_enemyMissile_[i].GetPositionX() - tank_.GetPositionX() >= 0) &&
			(v_enemyMissile_[i].GetPositionX() - tank_.GetPositionX() < 4)))
		{	//���� 4���� �۴ٸ� ��ũ���ϸ� ��ũ�� �����ȾƵ� �̻��Ͽ� �´°� ó�� �ȴ�. =>��ũ�� ũ�⸦ ����ؼ� ����Ŵ�.
			tank_.SetLife(tank_.GetLife() - 1);// ��ũ�� �������� ���� ���������� -1 �ȴ�.
			v_enemyMissile_[i].SetLife(0);//�̻����� �������. ������ �����ߴ�.
			if (tank_.GetLife() == 0)// ��ũ �������� 0�̸�
			{
				over_.GameOver();//���� ����
			}
		}
	}
}

void CGame::TMtowall()//��ũ �̻����� ���� ����
{
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_tankMissile_[i].GetPositionY() == v_wall_[j].GetPositionY() + 1) &&//�̷��� �� ������ �̻����� y��ǥ�� ���� �����Ѱ� �ƴ϶� ������ y+1 ��ŭ ���˵Ǿ� �´°� �̴�.
				((v_tankMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() >= -1) &&//-1���� ũ�� ���� ������ ��ũ �̻��Ͽ� ������ �μ�����. 
				(v_tankMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() < 5)))//5���� ũ�� ������ ������ ��ũ �̻��Ͽ� �¾ �μ�����.
			{	//��ũ�̻��� ��ǥ���� �� ��ǥ������ 0<= x <5 �������� ���� ũ�⸦ ����ؼ� �Ѱ� �̴�.
				v_tankMissile_[i].SetLife(0);//��ũ �̻����� ���� ������ �� ������
				gotoxy(v_tankMissile_[i].GetPositionX(), v_tankMissile_[i].GetPositionY());
				cout<<"  ";//�� ��ġ������ " " �� ���

			}
		}
	}
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_tankMissile_[i].GetPositionY() == v_wall_a_[j].GetPositionY()+1) &&//�̷��� �� ������ �̻����� y��ǥ�� ���� �����Ѱ� �ƴ϶� ������ y+1 ��ŭ ���˵Ǿ� �´°� �̴�.
				((v_tankMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= -1) &&//-1���� ũ�� ���� ������ ��ũ �̻��Ͽ� ������ �μ�����. 
				(v_tankMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 6)))//6���� ũ�� ������ ������ ��ũ �̻��Ͽ� �¾ �μ�����.
			
			{	v_tankMissile_[i].SetLife(0);//��ũ �̻����� ���� ������ �� ������
				gotoxy(v_tankMissile_[i].GetPositionX(), v_tankMissile_[i].GetPositionY());
				cout<<" ";//�� ��ġ������ " " �� ���
			}
		}
	}
}

void CGame::TMtoenemy()//��ũ �̻����� ���� �ε�ħ
{
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		for (int j = 0; j < v_enemy_.size(); j++)
		{
			if ((v_tankMissile_[i].GetPositionY() == v_enemy_[j].GetPositionY()) &&//��ũ �̻��ϰ� �� y ���� ���� => �浹
				((v_tankMissile_[i].GetPositionX() - v_enemy_[j].GetPositionX() >= -1) && 
				(v_tankMissile_[i].GetPositionX() - v_enemy_[j].GetPositionX() < 6)))
			{	//�� ������ ���� ũ�⸦ ����ؼ� �Ѱ��̴�. ���� ��� �κ��� �¾ �´°����� �ؾ��ϱ⿡
				v_tankMissile_[i].SetLife(0);//�̻����� ���� ��´� �� �״´�.
				v_enemy_[j].SetLife(v_enemy_[j].GetLife() - 1);//���� ���� -1
			}
		}
	}
}

void CGame::IMtowall()//���̻����� ���� ������
{
	for (int j = 0; j < v_wall_.size(); j++)
	{
		for (int i = 0; i < v_enemyMissile_.size(); i++)
		{
			if ((v_enemyMissile_[i].GetPositionY() == v_wall_[j].GetPositionY() - 1) &&//���̻����� ������ y�� -1�϶� �� ���� �浹  y��ǥ�� ���� �����Ѱ� �ƴ϶� ������ y-1 ��ŭ ���˵Ǿ� �´°� �̴�.
				((v_enemyMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() >= 0) && 
				(v_enemyMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() < 5)))
			{	//�� ũ�⿡ ���� ���� ����
				
				gotoxy(v_enemyMissile_[i].GetPositionX(), v_enemyMissile_[i].GetPositionY());
				cout<<" ";//���� ���� �κ��� " "�� ��� �����شٴ� �ǹ�
				v_enemyMissile_.erase(v_enemyMissile_.begin() + i);
				//begin i��° ���Ҹ� ������ ���� ������ �ݺ��� 
				//erase : �ݺ��� ���Ҹ� �����Ѵ�.=> �ǳ� �̻��� �����. �����ڸ��� enemy.c ���� ' ' �� ǥ��
			}	//�迭 ������ �� ������� �Ѵ�.
		}
	}
	for (int j = 0; j < v_wall_a_.size(); j++)
	{
		for (int i = 0; i < v_enemyMissile_.size(); i++)
		{
			if ((v_enemyMissile_[i].GetPositionY() == v_wall_a_[j].GetPositionY() - 1) &&//���̻����� ������ y�� -1�϶� �� ���� �浹  y��ǥ�� ���� �����Ѱ� �ƴ϶� ������ y+1 ��ŭ ���˵Ǿ� �´°� �̴�.
				((v_enemyMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= 0) && 
				(v_enemyMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 6)))
			{	//�� ũ�⿡ ���� ���� ����
				
				gotoxy(v_enemyMissile_[i].GetPositionX(), v_enemyMissile_[i].GetPositionY());
				cout<<" ";//���� ���� �κ��� " "�� ��� �����شٴ� �ǹ�
				v_enemyMissile_.erase(v_enemyMissile_.begin() + i);
				//begin i��° ���Ҹ� ������ ���� ������ �ݺ��� 
				//erase : �ݺ��� ���Ҹ� �����Ѵ�.=> �ǳ� �̻��� �����. �����ڸ��� enemy.c ���� ' ' �� ǥ��
			}
		}
	}

}

void CGame::enemyTowall()//���� ���� �浹
{
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_enemy_[i].GetPositionY() == v_wall_[j].GetPositionY())&&//���� ���� y ��ǥ ����.
				((v_enemy_[i].GetPositionX() == v_wall_[j].GetPositionX() + 2)))//���� ���� x ����. ũ�⸦ ����� +2 �̴�.
			{
				gotoxy(v_wall_[j].GetPositionX(), v_wall_[j].GetPositionY());//���� ���� �ε����� ���� ��������.
				cout<<"     ";//��ĭ ���
				v_wall_.erase(v_wall_.begin() + j);
				//���� j ��° ������ �����.
			}
		}
	}
for (int i = 0; i < v_enemy_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_enemy_[i].GetPositionY() == v_wall_a_[j].GetPositionY())&&//���� ���� y ��ǥ ����.
				((v_enemy_[i].GetPositionX() == v_wall_a_[j].GetPositionX() + 2)))//���� ���� x ����. ũ�⸦ ����� +2 �̴�.
			{
				gotoxy(v_wall_a_[j].GetPositionX(), v_wall_a_[j].GetPositionY());//���� ���� �ε����� ���� ��������.
				cout<<"     ";//��ĭ ���
				v_wall_a_.erase(v_wall_a_.begin() + j);
				//���� j ��° ������ �����.
			}
		}
	}
}

void CGame::UMtoTank()//���� �̻��ϰ� ��ũ�� �浹
{
	COver over_;
	CGame game_;

	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		if ((v_bossMissile_[i].GetPositionY() == 29) &&//���� �̻����� ��ũ ��ġ y ����.
			((v_bossMissile_[i].GetPositionX() - tank_.GetPositionX() >= 0) && 
				(v_bossMissile_[i].GetPositionX() - tank_.GetPositionX() < 4)))
		{		//��ũ ũ�⿡ ���� ���� ����
				over_.GameOver();//���� ���� erase �Ұ;��� ���� �ȴ�.
		}
	}
}

void CGame::UMtowall()//���� �̻��� ���� �浹
{
	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_bossMissile_[i].GetPositionY() == v_wall_[j].GetPositionY() - 1) &&//�浹 y ��ǥ -1 �̿����Ѵ�. �ε�ġ�°��̱� ������
				((v_bossMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() >= 0) &&
				(v_bossMissile_[i].GetPositionX() - v_wall_[j].GetPositionX() < 5)))
			{	//���� ũ�⿡ ���� ���� ����
				v_bossMissile_[i].SetLife(0);//���� �̻��� �Ҹ�ȴ�.
				gotoxy(v_bossMissile_[i].GetPositionX(), v_bossMissile_[i].GetPositionY());
				cout<<" ";
			}
		}
	}
	for (int i = 0; i < v_bossMissile_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_bossMissile_[i].GetPositionY() == v_wall_a_[j].GetPositionY() - 1) &&//�浹 y ��ǥ -1 �̿����Ѵ�. �ε�ġ�°��̱� ������
				((v_bossMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= 0) &&
				(v_bossMissile_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 6)))
			{	//���� ũ�⿡ ���� ���� ����
				v_bossMissile_[i].SetLife(0);//���� �̻��� �Ҹ�ȴ�.
				gotoxy(v_bossMissile_[i].GetPositionX(), v_bossMissile_[i].GetPositionY());
				cout<<" ";
			}
		}
	}
}
void CGame::TMtoboss()//��ũ �̻��� ���� ����
{
	CGame game_;
	for (int i = 0; i < v_tankMissile_.size(); i++)
	{
		if ((v_tankMissile_[i].GetPositionY() == 0) &&//������ �̻��� �浹
			((v_tankMissile_[i].GetPositionX() - boss_.GetPositionX() >= 0) &&
			(v_tankMissile_[i].GetPositionX() - boss_.GetPositionX() < 5)))
		{	//ũ�⿡ ���� ����
			boss_.SetLife(boss_.GetLife() - 1);//�̻��� ������ ���� ������ 1�� �Ҹ�
		}
		if (boss_.GetLife() == 0)//���������� 0 �̸�
		{
			NextStage();//���� ��������
		}
	}
}

void CGame::enemyToTank()//���� ��ũ�� �浹
{
	COver over_;
	CGame game_;
	for (int i = 0; i < v_enemy_.size(); i++)
	{
		if (v_enemy_[i].GetPositionY() == 29)//��ũ ��ġ
		{
			over_.GameOver();//���� ����
		}
	}
}

void CGame::ItemTowall()//�����۰� �� �浹
{
	for (int i = 0; i < v_object_.size(); i++)
	{
		for (int j = 0; j < v_wall_.size(); j++)
		{
			if ((v_object_[i].GetPositionY() == v_wall_[j].GetPositionY() - 1) &&//�浹
				((v_object_[i].GetPositionX() - v_wall_[j].GetPositionX() >= -2) &&
				(v_object_[i].GetPositionX() - v_wall_[j].GetPositionX() < 6)))
			{	//ũ�⿡ ���� ���� ����
				v_object_[i].SetLife(0);//�Ҹ�ȴ�.
				gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
				cout<<"     ";
			}
		}
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetLife() == 0)
		{
			v_object_.erase(v_object_.begin() + i);//i ��ŭ ��ȯ�Ͽ� �����
		}
	}

	for (int i = 0; i < v_object_.size(); i++)
	{
		for (int j = 0; j < v_wall_a_.size(); j++)
		{
			if ((v_object_[i].GetPositionY() == v_wall_a_[j].GetPositionY() - 1) &&//�浹
				((v_object_[i].GetPositionX() - v_wall_a_[j].GetPositionX() >= -2) &&
				(v_object_[i].GetPositionX() - v_wall_a_[j].GetPositionX() < 5)))
			{	//ũ�⿡ ���� ���� ����
				v_object_[i].SetLife(0);//�Ҹ�ȴ�.
				gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
				cout<<"     ";
			}
		}
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetLife() == 0)//�Ҹ�ɽ�
		{
			v_object_.erase(v_object_.begin() + i);//i ��ŭ ��ȯ�Ͽ� �����
		}
	}
}

void CGame::ItemToTank()//�������� ��ũ�� ������
{	
	for (int i = 0; i < v_object_.size(); i++)
	{
		if ((v_object_[i].GetPositionY() == 29) &&//��ũ ��ġ�� ����.
			((v_object_[i].GetPositionX() - tank_.GetPositionX() >= 0) &&
			(v_object_[i].GetPositionX() - tank_.GetPositionX() < 3)))
		{	//ũ�⿡ ���� ����
			v_object_[i].SetLife(0);//��Ƽ� �Ҹ�ȴ�.
			gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
			cout<<"   ";//" " �� ���
			tank_.SetLife(tank_.GetLife() + 1);//��ũ ������ 1����
		}
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetLife() == 0)
		{
			v_object_.erase(v_object_.begin() + i);//i ��ŭ ��ȯ�Ͽ� �����
		}
	}
	gotoxy(38, 32);
	cout<<"                     ";
	gotoxy(38, 32);
	for (int i = 1; i < tank_.GetLife(); i++)//��ũ �������� �����Ҷ� => �� �Ծ�����
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
		printf("[��]");
	}

	SetColor(7);
}

void CGame::itemdrop()
{
	CItem item_;

	itemValue++;
	if (itemValue == 200)//100�̸� ������ �������� ������ �� ����.
	{	
		CObject object_;
		object_.SetPositionX(rand() % 51);//X�� 0~50 ������ ��ġ���� ���� ������ �Ϻ�
		object_.SetPositionY(0);//Y�� 0
		v_object_.push_back(object_);// ��ȯ�Ѵ�.
		itemValue = 0;//�ٽ� �ʱ�ȭ
	}
	for (int i = 0; i < v_object_.size(); i++)
	{
		if (v_object_[i].GetPositionY() < 29)//Y�� 29���� ������
		{
			gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());//������ġ���� ' ' ����
			cout<<"    ";
			v_object_[i].SetPositionY(v_object_[i].GetPositionY() + 1);// ������ġ���� Y �� +1�̸� ������ ��� ���
			gotoxy(v_object_[i].GetPositionX(), v_object_[i].GetPositionY());
			item_.Print();
		}
	}
}