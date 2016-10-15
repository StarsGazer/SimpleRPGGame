#include"stdafx.h"

#include"Character.h"
#include"Weapen.h"
#include"Technique.h"
#include"FileIO.h"
#include"BattleSystem.h"
#include"GameController.h"//Provide the variable "GameHero"

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>

extern Hero GameHero;
extern GameController MyController;
extern FileIO fileIO;
bool if_hero_can_move = false;
bool if_enemy_can_move = false;
bool if_teammate_can_move = false;
bool if_hero_can_attack = false;
bool if_teammate_can_attack = false;

void BattleSystem::CalculateDemage(Enemy &enemy,const string &msg,const string&kind)
{

	srand((unsigned)time(NULL));
	bool If_onehit = false;
	bool If_restrain = false;//If true, demage+1,hitrate+10
	
	if (msg == "attack")//The hero attacks the enemy.
	{
		If_restrain = this->RestrainCheck(enemy, GameHero, "attack");
		int demage = 0;
		//Calculation of the onehit(必杀率) of the hero's weapen.
		int onehit = 100 * (GameHero.GetCurrentWeapen().GetOnehit() + GameHero.GetAbility("technique")*0.015 );
		int hitrate = 100 * (GameHero.GetCurrentWeapen().Gethitrate() + (GameHero.GetAbility("agility") - enemy.GetAbility("agility"))*0.05);//Calculation of the hitrate(命中率) of the hero.
		if (If_restrain == RESTRAIN_SUCCESS)
			hitrate += 10;
		else if (If_restrain == RESTRAIN_FAIL)
			hitrate -= 10;
		if (onehit > (rand() % 100))
		{
			If_onehit = true;
		}
		if (If_onehit==true||hitrate>(rand()%100))//Then the hero successfully hit the enemy.
			//When If_onehit is true, the hitrate will be ignored.
		{
			if (If_onehit == true)//The demage will mutiply by 2.
			{
				if (kind == "physics")//If the attack is physics attack.
				{
					demage = GameHero.GetCurrentWeapen().GetAttack()+ GameHero.GetAbility("attack") - enemy.GetAbility("defend");
					demage *= 2;//Onehit.(必杀)
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
				else if(kind=="magic")
				{
					demage = GameHero.GetCurrentWeapen().GetAttack() + GameHero.GetAbility("magicpower") - enemy.GetAbility("defend") / 2;
					demage *= 2;
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
			}
			else
			{	
				if(kind=="physics")
					demage = GameHero.GetCurrentWeapen().GetAttack() + GameHero.GetAbility("attack") - enemy.GetAbility("defend");
				else if(kind=="magic")
					demage = GameHero.GetCurrentWeapen().GetAttack() + GameHero.GetAbility("magicpower") - enemy.GetAbility("defend") / 2;
				if (If_restrain == RESTRAIN_SUCCESS)
					demage += 1;
				else if (If_restrain == RESTRAIN_FAIL)
					demage -= 1;
			}
		}
		if (GameHero.GetCurrentWeapen().GetEndurance() == 0)
		{
			demage = 0;//If the endurance of the weapen is 0,the hero will fail to attack.
		}
		enemy.ChangeAbility("life", -demage);//The life of the enemy will reduce.
	}
	else if (msg == "defend")//The hero is attacked.
	{
		If_restrain = this->RestrainCheck(enemy, GameHero, "defend");
		int demage = 0;
		//Calculation of the onehit(必杀率) of the enemy's weapen.
		int onehit = 100 * (enemy.GetCurrentWeapen().GetOnehit() +enemy.GetAbility("technique")*0.015 );
		int hitrate = 100 * (enemy.GetCurrentWeapen().Gethitrate() + (enemy.GetAbility("agility") - GameHero.GetAbility("agility"))*0.05);//Calculation of the hitrate(命中率) of the enemy.
		if (If_restrain == RESTRAIN_SUCCESS)
			hitrate += 10;
		else if (If_restrain == RESTRAIN_FAIL)
			hitrate -= 10;
		if (onehit > (rand() % 100))
		{
			If_onehit = true;
		}
		if (If_onehit == true || hitrate>(rand() % 100))//Then the hero successfully hit the hero.
														//When If_onehit is true, the hitrate will be ignored.
		{
			if (If_onehit == true)//The demage will mutiply by 2.
			{
				if (kind == "physics")//If the attack is physics attack.
				{
					demage = enemy.GetAbility("attack") + enemy.GetCurrentWeapen().GetAttack() - GameHero.GetAbility("defend");
					demage *= 2;//Onehit.(必杀)
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
				else if (kind == "magic")
				{
					demage = enemy.GetCurrentWeapen().GetAttack()+ enemy.GetAbility("magicpower") - GameHero.GetAbility("defend") / 2;
					demage *= 2;
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
			}
			else
			{
				if (kind == "physics")
					demage = enemy.GetAbility("attack") + enemy.GetCurrentWeapen().GetAttack() - GameHero.GetAbility("defend");
				else if (kind == "magic")
					demage = enemy.GetCurrentWeapen().GetAttack() + enemy.GetAbility("magicpower") - GameHero.GetAbility("defend") / 2;
				if (If_restrain == RESTRAIN_SUCCESS)
					demage += 1;
				else if (If_restrain == RESTRAIN_FAIL)
					demage -= 1;
			}
		}

		GameHero.ChangeAbility("life", -demage);//The life of the hero will reduce.
	}
}

void BattleSystem::CalculateDemage(Enemy &enemy, Teammate&teammate,const string &msg, const string&kind)
{

	srand((unsigned)time(NULL));
	bool If_onehit = false;
	bool If_restrain = false;//If true, demage+1,hitrate+10.

	if (msg == "attack")//The teammate attacks the enemy.
	{
		int demage = 0;
		If_restrain=this->RestrainCheck(enemy, teammate, "attack");
		//Calculation of the onehit(必杀率) of the teammate's weapen.
		int onehit = 100 * (teammate.GetCurrentWeapen().GetOnehit() + teammate.GetAbility("technique")*0.015 );
		int hitrate = 100 * (teammate.GetCurrentWeapen().Gethitrate() + (teammate.GetAbility("agility") - enemy.GetAbility("agility"))*0.05);//Calculation of the hitrate(命中率) of the teammate.
		if (If_restrain == RESTRAIN_SUCCESS)
			hitrate += 10;
		else if (If_restrain == RESTRAIN_FAIL)
			hitrate -= 10;
		if (onehit > (rand() % 100))
		{
			If_onehit = true;
		}
		if (If_onehit == true || hitrate>(rand() % 100))//Then the teammate successfully hit the enemy.
														//When If_onehit is true, the hitrate will be ignored.
		{
			if (If_onehit == true)//The demage will mutiply by 2.
			{
				if (kind == "physics")//If the attack is physics attack.
				{
					demage = teammate.GetCurrentWeapen().GetAttack() + teammate.GetAbility("attack") - enemy.GetAbility("defend");
					demage *= 2;//Onehit.(必杀)
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
				else if (kind == "magic")
				{
					demage = teammate.GetCurrentWeapen().GetAttack() + teammate.GetAbility("magicpower") - enemy.GetAbility("defend") / 2;
					demage *= 2;
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
			}
			else
			{
				if (kind == "physics")
					demage = teammate.GetCurrentWeapen().GetAttack() + teammate.GetAbility("attack") - enemy.GetAbility("defend");
				else if (kind == "magic")
					demage = teammate.GetCurrentWeapen().GetAttack() + teammate.GetAbility("magicpower") - enemy.GetAbility("defend") / 2;
				if (If_restrain == RESTRAIN_SUCCESS)
					demage += 1;
				else if (If_restrain == RESTRAIN_FAIL)
					demage -= 1;
			}
		}
		if (teammate.GetCurrentWeapen().GetEndurance() == 0)
		{
			demage = 0;
			//
		}
		enemy.ChangeAbility("life", -demage);//The life of the enemy will reduce.
	}
	else if (msg == "defend")//The teammate is attacked.
	{
		int demage = 0;
		If_restrain = this->RestrainCheck(enemy, teammate, "defend");
		//Calculation of the onehit(必杀率) of the enemy's weapen.
		int onehit = 100 * (enemy.GetCurrentWeapen().GetOnehit() + enemy.GetAbility("technique")*0.015);
		int hitrate = 100 * (enemy.GetCurrentWeapen().Gethitrate() + (enemy.GetAbility("agility") - teammate.GetAbility("agility"))*0.05);//Calculation of the hitrate(命中率) of the enemy.
		if (If_restrain == RESTRAIN_SUCCESS)
			hitrate += 10;
		else if (If_restrain == RESTRAIN_FAIL)
			hitrate -= 10;
		if (onehit > (rand() % 100))
		{
			If_onehit = true;
		}
		if (If_onehit == true || hitrate>(rand() % 100))//Then the enemy successfully hit the teammate.
														//When If_onehit is true, the hitrate will be ignored.
		{
			if (If_onehit == true)//The demage will mutiply by 2.
			{
				if (kind == "physics")//If the attack is physics attack.
				{
					demage = enemy.GetAbility("attack") + enemy.GetCurrentWeapen().GetAttack() - teammate.GetAbility("defend");
					demage *= 2;//Onehit.(必杀)
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
				else if (kind == "magic")
				{
					demage = enemy.GetCurrentWeapen().GetAttack() + enemy.GetAbility("magicpower") - teammate.GetAbility("defend") / 2;
					demage *= 2;
					if (If_restrain == RESTRAIN_SUCCESS)
						demage += 1;
					else if (If_restrain == RESTRAIN_FAIL)
						demage -= 1;
				}
			}
			else
			{
				if (kind == "physics")
					demage = enemy.GetAbility("attack") + enemy.GetCurrentWeapen().GetAttack() - teammate.GetAbility("defend");
				else if (kind == "magic")
					demage = enemy.GetCurrentWeapen().GetAttack() + enemy.GetAbility("magicpower") - teammate.GetAbility("defend") / 2;
				if (If_restrain == RESTRAIN_SUCCESS)
					demage += 1;
				else if (If_restrain == RESTRAIN_FAIL)
					demage -= 1;
			}
		}
		teammate.ChangeAbility("life", -demage);//The life of the teammate will reduce.
	}
}

int BattleSystem::RestrainCheck(Enemy& enemy,Hero& hero,const string&msg)
{
	if (msg == "attack")
	{
		//Weapen and career.
		if (hero.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetName() == "knight")
			return RESTRAIN_SUCCESS;
		else if (hero.GetName() == "knight"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_FAIL;
		//Magic weapens.
		else if (hero.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_FAIL;
		//Physics weapens.
		else if (hero.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "arch"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "arch")
			return RESTRAIN_FAIL;
	}
	else if (msg == "defend")
	{
		//Weapen and career.
		if (hero.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetName() == "knight")
			return RESTRAIN_FAIL;
		else if (hero.GetName() == "knight"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_SUCCESS;
		//Magic weapens.
		else if (hero.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_SUCCESS;
		//Physics weapens.
		else if (hero.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_SUCCESS;
		else if (hero.GetCurrentWeapen().GetProperty() == "arch"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_FAIL;
		else if (hero.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "arch")
			return RESTRAIN_SUCCESS;
	}
}

int BattleSystem::RestrainCheck(Enemy& enemy, Teammate&teammate, const string&msg)
{
	if (msg == "attack")
	{
		//Weapen and career.
		if (teammate.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetName() == "knight")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetName() == "knight"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_FAIL;
		//Magic weapens.
		else if (teammate.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_FAIL;
		//Physics weapens.
		else if (teammate.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "arch"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "arch")
			return RESTRAIN_FAIL;
	}
	else if (msg == "defend")
	{
		//Weapen and career.
		if (teammate.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetName() == "knight")
			return RESTRAIN_FAIL;
		else if (teammate.GetName() == "knight"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_SUCCESS;
		//Magic weapens.
		else if (teammate.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "ice"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "ice")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "thunder"&&enemy.GetCurrentWeapen().GetProperty() == "fire")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "fire"&&enemy.GetCurrentWeapen().GetProperty() == "thunder")
			return RESTRAIN_SUCCESS;
		//Physics weapens.
		else if (teammate.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "axe"&&enemy.GetCurrentWeapen().GetProperty() == "sword")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "sword"&&enemy.GetCurrentWeapen().GetProperty() == "axe")
			return RESTRAIN_SUCCESS;
		else if (teammate.GetCurrentWeapen().GetProperty() == "arch"&&enemy.GetCurrentWeapen().GetProperty() == "lance")
			return RESTRAIN_FAIL;
		else if (teammate.GetCurrentWeapen().GetProperty() == "lance"&&enemy.GetCurrentWeapen().GetProperty() == "arch")
			return RESTRAIN_SUCCESS;
	}
}

void BattleSystem::CalculateExp(Enemy&enemy)
{
	if (enemy.GetEnemyKind() == "normal")//If the normal enemy is defeated.
	{
		int exp = 10 + (enemy.GetLevel() - GameHero.GetLevel()) * 3;
		if (exp < 1)
			exp = 1;//The hero gains at least 1 exp.
		GameHero.SetExp(GameHero.GetExp() +exp);

		if (GameHero.GetExp()>=100)//Level up when the hero's exp is over 100.
		{
			GameHero.LevelUp();
			GameHero.SetExp(GameHero.GetExp() - 100);//The next level's exp.At least 0.
		}
	}
	else if (enemy.GetEnemyKind() == "boss")//If the boss is defeated.
	{
		int exp = 30 + (enemy.GetLevel() - GameHero.GetLevel()) * 5;
		if (exp < 10)
			exp = 10;//The hero gains at least 10 exp.
		GameHero.SetExp(GameHero.GetExp() + exp);

		if (GameHero.GetExp() >= 100)//Level up when the hero's exp is over 100.
		{
			GameHero.LevelUp();
			GameHero.SetExp(GameHero.GetExp() - 100);//The next level's exp.At least 0.
		}
	}
}

void BattleSystem::CalculateMoney(Enemy&enemy)
{
	srand((unsigned)time(NULL));
	int level_distance = enemy.GetLevel() - GameHero.GetLevel();
	if (level_distance <= 0)
		level_distance = 1;
	int money = level_distance * 100 + GameHero.GetAbility("fortune")*rand()%10;
	if(GameHero.GetAbility("fortune")*3>(rand()%100))//Whether the hero can gain the money depends on the fortune.
		GameHero.SetMoney(GameHero.GetMoney() + money);
}

void BattleSystem::BattleStart(const string&filename)
{
	MyController.SetBattleStart();//Set the battle start 
	//and then change the scene.
	GameScene().DialogClear();
	if (!fileIO.IfNoEnemy())
	{
		//Read from the saveddata and initialize the information of the current enemies.
		for (size_t i = 0; i != fileIO.GetEnemyAmountOfFile(); ++i)
		{
			enemies.push_back(fileIO.GetEnemyAtIndex(i));//Get the enemies from the saveddata.
		}
	}
	else
		this->InitializingEnemies(filename);
	if (!fileIO.IfNoTeammate())
	{
		//Read from the saveddata and initialize the information of the current teammates.
		for (size_t i = 0; i != fileIO.GetTeammateAmountOfFile(); ++i)
		{
			teammates.push_back(fileIO.GetTeammateAtIndex(i));//Get the teammates from the saveddata.
		}
	}
	else
		this->InitializingTeammates(filename);
}

void BattleSystem::InitializingEnemies(const string&filename)
{
	//Based on the plot.So the fileIO will be used.

}

void BattleSystem::InitializingTeammates(const string&filename)
{
	//Based on the plot.So the fileIO will be used.
}

void BattleSystem::CursorFlashing()
{
	++cursor_flashing_count;
	if (cursor_flashing_count == 5000)
	{
		GameController().SetPosition(cursor_position.first, cursor_position.second);//private function
		cout << cursor << flush;
	}
	else if (cursor_flashing_count == 10000)
	{
		GameController().SetPosition(cursor_position.first, cursor_position.second);
		cout << " " << flush;
		cursor_flashing_count = 0;
	}
}

void BattleSystem::Battling()
{
	if (if_hero_attack_enemy)//If the hero attacks the enemy.
	{
		this->CalculateDemage(this->GetEnemyAtIndex(current_enemy_index), "attack", current_attack_type);
		if (this->GetEnemyAtIndex(current_enemy_index).GetAbility("life") <= 0)
		{
			this->CalculateExp(GetEnemyAtIndex(current_enemy_index));
			//Delete the enemy from the vector.
			int i = 0;
			for (auto it = enemies.begin(); it != enemies.end(); ++it,++i)
			{
				if (i == current_enemy_index)
					it = enemies.erase(it);//Delete the defeated enemy.
			}
		}
		if_hero_attack_enemy = false;//Avoid calculating the deamge again.
	}
	else if (if_enemy_attack_hero)//If the hero is attacked by the enemy.
	{
		this->CalculateDemage(this->GetEnemyAtIndex(current_enemy_index), "defend", current_attack_type);
		if (GameHero.GetAbility("life") <= 0)
		{
			//The hero if defeated,then the battle is over.

		}
		if_enemy_attack_hero = false;
	}
	else if (if_teammate_attack_enemy)//If the teammate attacks the enemy.
	{
		this->CalculateDemage(this->GetEnemyAtIndex(current_enemy_index), this->GetTeammateAtIndex(current_teammate_index), "attack", current_attack_type);
		if (this->GetEnemyAtIndex(current_enemy_index).GetAbility("life") <= 0)
		{
			this->CalculateExp(GetEnemyAtIndex(current_enemy_index));
			//Delete the enemy from the vector.
			int i = 0;
			for (auto it = enemies.begin(); it != enemies.end(); ++it, ++i)
			{
				if (i == current_enemy_index)
					it = enemies.erase(it);//Delete the defeated enemy.
			}
		}
		if_teammate_attack_enemy = false;
	}
	else if (if_enemy_attack_teammate)//If the teammate is attacked by the enemy.
	{
		this->CalculateDemage(this->GetEnemyAtIndex(current_enemy_index), this->GetTeammateAtIndex(current_teammate_index), "defend", current_attack_type);
		if (this->GetTeammateAtIndex(current_teammate_index).GetAbility("life") <= 0)
		{
			//Delete the teammate from the vector.
			int i = 0;
			for (auto it = teammates.begin(); it != teammates.end(); ++it, ++i)
			{
				if (i == current_teammate_index)
					it = teammates.erase(it);//Delete the defeated enemy.
			}
		}
		if_enemy_attack_teammate = false;
	}
}

void BattleSystem::BattleOver()
{
	GameScene().DrawBattleEndInformation();
}

void BattleSystem::EnemyPlaying()
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		//Check whether the enemy can attack hero or the hero's teammates.
		hero_will_be_attacked = false;
		bool if_enemy_can_attack = IfEnemyCanAttack((*it).GetCurrentWeapen().GetRange(), { (*it).GetPositionX(),(*it).GetPositionY() });
		if (if_enemy_can_attack)//How the enemy attack.
		{
			//The enemy will choose the nearest one to attack.

		}
		//Move the enemy.

		//Check whether the enemy can attack hero or the hero's teammates again.
		hero_will_be_attacked = false;
		if_enemy_can_attack = IfEnemyCanAttack((*it).GetCurrentWeapen().GetRange(), { (*it).GetPositionX(),(*it).GetPositionY() });
		if (if_enemy_can_attack)//How the enemy attack.
		{

		}
	}
}

bool BattleSystem::IfEnemyCanAttack(int range, pair<int, int>current_position)//The funtion will also be used to show the range directly.
{
	//current_position = { GetEnemyAtIndex(current_enemy_index).GetPositionX(),GetEnemyAtIndex(current_enemy_index).GetPositionY() };

	teammates_to_be_attacked.clear();

	if (range == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "■" << flush;
		return true;
	}

	static bool  if_enemy_can_attack = false;

	IfEnemyCanAttack(--range, { current_position.first + 1,current_position.second });
	range++;
	IfEnemyCanAttack(--range, { current_position.first - 1,current_position.second });
	range++;
	IfEnemyCanAttack(--range, { current_position.first,current_position.second + 1 });
	range++;
	IfEnemyCanAttack(--range, { current_position.first,current_position.second - 1 });

	MyController.SetPosition(current_position.first, current_position.second);
	cout << "■" << flush;//Let the player know the range directly.

	//Then check the hero or the teammates around this position.
	if (current_position.first == GameHero.GetPositionX() && abs(current_position.second - GameHero.GetPositionY()) == 1)
	{
		if_enemy_can_attack = true;
		hero_will_be_attacked = true;
	}
	else if (current_position.second == GameHero.GetPositionY() && abs(current_position.first - GameHero.GetPositionX()) == 1)
	{
		if_enemy_can_attack = true;
		hero_will_be_attacked = true;
	}
	
	else
	{
		for (int i = 0; i != GetTeammateAmount(); ++i)
		{
			if (current_position.first == GetTeammateAtIndex(i).GetPositionX() && abs(current_position.second - GetTeammateAtIndex(i).GetPositionY()) == 1)
			{
				if_enemy_can_attack = true;
				teammates_to_be_attacked.push_back(GetTeammateAtIndex(i));
			}
			else if (current_position.second == GetTeammateAtIndex(i).GetPositionY() && abs(current_position.first - GetTeammateAtIndex(i).GetPositionX()) == 1)
			{
				if_enemy_can_attack = true;
				teammates_to_be_attacked.push_back(GetTeammateAtIndex(i));
			}
		}
	}

	return if_enemy_can_attack;
}

bool BattleSystem::IfHeroCanAttack(int range,pair<int,int>current_position)//The funtion will also be used to show the range directly.
{
	//pair<int, int>current_position = { GameHero.GetPositionX(),GameHero.GetPositionY() };

	if (range == 0)
	{
		return true;
	}

	IfHeroCanAttack(--range, { current_position.first + 1,current_position.second });
	range++;
	IfHeroCanAttack(--range, { current_position.first - 1,current_position.second });
	range++;
	IfHeroCanAttack(--range, { current_position.first,current_position.second + 1 });
	range++;
	IfHeroCanAttack(--range, { current_position.first,current_position.second - 1 });

	//Then check the enemy around this position.
	for (int i = 0; i != GetEnemyAmount(); ++i)
	{
		if (current_position.first == this->GetEnemyAtIndex(i).GetPositionX() && abs(current_position.second - this->GetEnemyAtIndex(i).GetPositionY()) == 1)
		{
			if_hero_can_attack = true;
			current_enemy_index = i;
		}
		else if (current_position.second == this->GetEnemyAtIndex(i).GetPositionY() && abs(current_position.first - this->GetEnemyAtIndex(i).GetPositionX()) == 1)
		{
			if_hero_can_attack = true;
			current_enemy_index = i;
		}
	}

	return if_hero_can_attack;
}

bool BattleSystem::IfTeammateCanAttack(int range, pair<int, int>current_position)//The funtion will also be used to show the range directly.
{
	//current_position = { GetTeammateAtIndex(current_teammate_index).GetPositionX(),GetTeammateAtIndex(current_teammate_index).GetPositionY() };
	if (range == 0)
	{
		return true;
	}

	IfTeammateCanAttack(--range, { current_position.first + 1,current_position.second });
	range++;
	IfTeammateCanAttack(--range, { current_position.first - 1,current_position.second });
	range++;
	IfTeammateCanAttack(--range, { current_position.first,current_position.second + 1 });
	range++;
	IfTeammateCanAttack(--range, { current_position.first,current_position.second - 1 });


	//Then check the enemy around this position.
	for (int i = 0; i != GetEnemyAmount(); ++i)
	{
		if (current_position.first == GetEnemyAtIndex(i).GetPositionX() && abs(current_position.second - GetEnemyAtIndex(i).GetPositionY()) == 1)
			if_teammate_can_attack = true;
		else if (current_position.second == GetEnemyAtIndex(i).GetPositionY() && abs(current_position.first - GetEnemyAtIndex(i).GetPositionX()) == 1)
			if_teammate_can_attack = true;
	}

	return  if_teammate_can_attack;
}

bool BattleSystem::IfHeroCanMove(int movespeed,pair<int,int>current_position)
{
	//pair<int, int>current_position = { GameHero.GetPositionX(),GameHero.GetPositionY() };
	if (movespeed == 0)
	{
		return true;
	}

	IfHeroCanMove(--movespeed, { current_position.first + 1,current_position.second });
	movespeed++;
	IfHeroCanMove(--movespeed, { current_position.first - 1,current_position.second });
	movespeed++;
	IfHeroCanMove(--movespeed, { current_position.first,current_position.second + 1 });
	movespeed++;
	IfHeroCanMove(--movespeed, { current_position.first,current_position.second - 1 });

	if ((this->GetCursorPositionX() == current_position.first) && (this->GetCursorPositionY() == current_position.second))
	{
		if_hero_can_move = true;
	}

	return if_hero_can_move;
}

bool BattleSystem::IfEnemyCanMove(int movespeed, pair<int, int>current_position)
{
	//current_position = { GetEnemyAtIndex(current_enemy_index).GetPositionX(),GetEnemyAtIndex(current_enemy_index).GetPositionY() };
	if (movespeed == 0)
	{
		return true;
	}

	IfEnemyCanMove(--movespeed, { current_position.first + 1,current_position.second });
	movespeed++;
	IfEnemyCanMove(--movespeed, { current_position.first - 1,current_position.second });
	movespeed++;
	IfEnemyCanMove(--movespeed, { current_position.first,current_position.second + 1 });
	movespeed++;
	IfEnemyCanMove(--movespeed, { current_position.first,current_position.second - 1 });

	if ((this->GetCursorPositionX() == current_position.first) && (this->GetCursorPositionY() == current_position.second))
	{
		if_enemy_can_move = true;
	}

	return if_enemy_can_move;
}

bool BattleSystem::IfTeammateCanMove(int movespeed, pair<int, int>current_position)
{
	//current_position = { GetTeammateAtIndex(current_teammate_index).GetPositionX(),GetTeammateAtIndex(current_teammate_index).GetPositionY() };

	if (movespeed == 0)
	{
		return true;
	}

	IfTeammateCanMove(--movespeed, { current_position.first + 1,current_position.second });
	movespeed++;
	IfTeammateCanMove(--movespeed, { current_position.first - 1,current_position.second });
	movespeed++;
	IfTeammateCanMove(--movespeed, { current_position.first,current_position.second + 1 });
	movespeed++;
	IfTeammateCanMove(--movespeed, { current_position.first,current_position.second - 1 });

	if ((this->GetCursorPositionX() == current_position.first) && (this->GetCursorPositionY() == current_position.second))
	{
		if_teammate_can_move = true;
	}

	return if_teammate_can_move;
}

void BattleSystem::ShowHeroMoveArea(int movespeed, pair<int, int>current_position)
{
	//pair<int, int>current_position = { GameHero.GetPositionX(),GameHero.GetPositionY() };
	if (movespeed == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "□" << flush;
		return ;
	}

	ShowHeroMoveArea(--movespeed, { current_position.first + 1,current_position.second });
	movespeed++;
	ShowHeroMoveArea(--movespeed, { current_position.first - 1,current_position.second });
	movespeed++;
	ShowHeroMoveArea(--movespeed, { current_position.first,current_position.second + 1 });
	movespeed++;
	ShowHeroMoveArea(--movespeed, { current_position.first,current_position.second - 1 });

	MyController.SetPosition(current_position.first, current_position.second);
	cout << "□" << flush;//Let the player know the range directly.

	return ;
}

void BattleSystem::ShowEnemyMoveArea(int movespeed, pair<int, int>current_position)
{
	//current_position = { GetEnemyAtIndex(current_enemy_index).GetPositionX(),GetEnemyAtIndex(current_enemy_index).GetPositionY() };
	//movespeed=GetEnemyAtIndex(current_enemy_index).GetAbility("movespeed");
	if (movespeed == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "□" << flush;
		return;
	}

	ShowEnemyMoveArea(--movespeed, { current_position.first + 1,current_position.second });
	movespeed++;
	ShowEnemyMoveArea(--movespeed, { current_position.first - 1,current_position.second });
	movespeed++;
	ShowEnemyMoveArea(--movespeed, { current_position.first ,current_position.second + 1});
	movespeed++; 
	ShowEnemyMoveArea(--movespeed, { current_position.first ,current_position.second - 1});
	
	MyController.SetPosition(current_position.first, current_position.second);
	cout << "□" << flush;//Let the player know the range directly.

	return;
}

void BattleSystem::ShowTeammateMoveArea(int movespeed, pair<int, int>current_position)
{
	//current_position = { GetTeammateAtIndex(current_teammate_index).GetPositionX(),GetTeammateAtIndex(current_teammate_index).GetPositionY() };
	//movespeed= GetTeammateAtIndex(current_teammate_index).GetAbility("movespeed");
	if (movespeed == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "□" << flush;
		return;
	}

	ShowTeammateMoveArea(--movespeed, { current_position.first + 1,current_position.second });
	movespeed++;
	ShowTeammateMoveArea(--movespeed, { current_position.first - 1,current_position.second });
	movespeed++;
	ShowTeammateMoveArea(--movespeed, { current_position.first ,current_position.second + 1});
	movespeed++;
	ShowTeammateMoveArea(--movespeed, { current_position.first ,current_position.second - 1});

	MyController.SetPosition(current_position.first, current_position.second);
	cout << "□" << flush;//Let the player know the range directly.

	return;
}

void BattleSystem::ShowHeroAttackArea(int range, pair<int, int>current_position)
{
	//range=GameHero.GetCurrentWeapen().GetRange();
	//current_position={GameHero.GetPositionX(),GameHero.GetPositionY();}
	if (range == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "□" << flush;
		return;
	}

	ShowHeroAttackArea(--range, { current_position.first +1,current_position.second });
	range++;
	ShowHeroAttackArea(--range, { current_position.first - 1,current_position.second });
	range++;
	ShowHeroAttackArea(--range, { current_position.first,current_position.second + 1 });
	range++;
	ShowHeroAttackArea(--range, { current_position.first,current_position.second - 1 });

	MyController.SetPosition(current_position.first, current_position.second);
	cout << "□" << flush;//Let the player know the range directly.

	return;
}

void BattleSystem::ShowEnemyAttackArea(int range, pair<int, int>current_position)
{
	//range=GetEnemyAtIndex(current_enemy_index).GetCurrentWeapen().GetRange();
	//current_position={GetEnemyAtIndex(curretn_enemy_index).GetPositionX(),GetEnemyAtIndex(curretn_enemy_index).GetPositionY()};
	if (range == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "□" << flush;
		return;
	}

	ShowEnemyAttackArea(--range, { current_position.first + 1,current_position.second });
	range++;
	ShowEnemyAttackArea(--range, { current_position.first - 1,current_position.second });
	range++;
	ShowEnemyAttackArea(--range, { current_position.first,current_position.second + 1 });
	range++;
	ShowEnemyAttackArea(--range, { current_position.first,current_position.second - 1 });

	MyController.SetPosition(current_position.first, current_position.second);
	cout << "□" << flush;//Let the player know the range directly.

	return;
}

void BattleSystem::ShowTeammateAttackArea(int range, pair<int, int>current_position)
{
	//range=GetTeammateAtIndex(current_enemy_index).GetCurrentWeapen().GetRange();
	//current_position={GetTeammateAtIndex(curretn_enemy_index).GetPositionX(),GetTeammateAtIndex(curretn_enemy_index).GetPositionY()};
	if (range == 0)
	{
		MyController.SetPosition(current_position.first, current_position.second);
		cout << "□" << flush;
		return;
	}

	ShowTeammateAttackArea(--range, { current_position.first + 1,current_position.second });
	range++;
	ShowTeammateAttackArea(--range, { current_position.first - 1,current_position.second });
	range++;
	ShowTeammateAttackArea(--range, { current_position.first,current_position.second + 1 });
	range++;
	ShowTeammateAttackArea(--range, { current_position.first,current_position.second - 1 });

	MyController.SetPosition(current_position.first, current_position.second);
	cout << "□" << flush;//Let the player know the range directly.

	return;
}

void BattleSystem::HeroMoveAreaClear()
{
	pair<int, int>current_position = { GameHero.GetPositionX() - GameHero.GetAbility("movespeed") , GameHero.GetPositionY() - GameHero.GetAbility("movespeed") };

	for (int i = 0; i != GameHero.GetAbility("movespeed") * 2 + 1; ++i)
	{
		for (int j = 0; j != GameHero.GetAbility("movespeed") * 2 + 1; ++j)
		{
			MyController.SetPosition(current_position.first + i, current_position.second + j);
			cout << " " << flush;
		}
	}
}

void BattleSystem::HeroAttackAreaClear()
{
	pair<int, int>current_position = { GameHero.GetPositionX() - GameHero.GetCurrentWeapen().GetRange() , GameHero.GetPositionY() - GameHero.GetCurrentWeapen().GetRange() };

	for (int i = 0; i != GameHero.GetCurrentWeapen().GetRange() * 2 + 1; ++i)
	{
		for (int j = 0; j != GameHero.GetCurrentWeapen().GetRange() * 2 + 1; ++j)
		{
			MyController.SetPosition(current_position.first + i, current_position.second + j);
			cout << " " << flush;
		}
	}
}