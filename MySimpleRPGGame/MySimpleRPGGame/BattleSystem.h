#ifndef __BATTLE_SYSTEM_H__
#define __BATTLE_SYSTEM_H__

#define RESTRAIN_SUCCESS 1//demage+1
#define RESTRAIN_FAIL 0//demage-1
#define RESTRAIN_NONE 2//nothing happened

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<utility>

#include"Character.h"
#include"Weapen.h"

using std::map;
using std::vector;
using std::pair;

class BattleSystem {

public:
	BattleSystem() = default;


	void BattleStart(const string&filename);
	void Battling();
	void BattleOver();
	void CalculateDemage(Enemy &enemy, const string&msg, const string&kind);
	void CalculateDemage(Enemy&enemy, Teammate& teammate, const string&msg, const string&kind);
	void CalculateExp( Enemy&enemy);
	void CalculateMoney(Enemy&enemy);

	int GetCursorPositionX() { return cursor_position.first; }
	int GetCursorPositionY() { return cursor_position.second; }

	void SetCursorPositionX(int x) { cursor_position.first = x; }
	void SetCursorPositionY(int y) { cursor_position.second = y; }

	int GetBattleMenuCursorPositionX() { return battle_menu_cursor_position.first; }
	int GetBattleMenuCursorPositionY() { return battle_menu_cursor_position.second; }

	void SetBattleMenuCursorPositionX(int x) { battle_menu_cursor_position.first = x; }
	void SetBattleMenuCursorPositionY(int y) { battle_menu_cursor_position.second = y; }

	int GetEnemyAmount() { return enemies.size(); }
	Enemy& GetEnemyAtIndex(int index) { return enemies[index]; }//Get an enemy from "enemies".

	int GetTeammateAmount() { return teammates.size(); }
	Teammate& GetTeammateAtIndex(int index) { return teammates[index]; }

	void CursorFlashing();
	string GetCursorImage() { return cursor; }

	void SetHeroAttackEnemy() { if_hero_attack_enemy = true; }
	void SetEnemyAttackHero() { if_enemy_attack_hero = true; }
	void SetTeammateAttackEnemy() { if_teammate_attack_enemy = true; }
	void SetEnemyAttackTeammate() { if_enemy_attack_hero = true; }

	void SetCurrentEnemyIndex(int index) { current_enemy_index = index; }
	void SetCurrentTeammateIndex(int index) { current_teammate_index = index; }

	void SetCurrentAttackType(const string& t) { current_attack_type = t; }


	bool IfEnemyPlaying() { return if_enemy_playing; }
	void EnemyPlaying() ;//The things that the computer will do during its round.

	bool IfHeroCanMove(int movespeed,pair<int,int>current_position);/*When the player tries to let the hero move, the function will check if the distance is equal to
	the movespeed or smaller than the movespeed.*/
	bool IfEnemyCanMove(int movespeed, pair<int, int>current_position);/*When the enemies try to let the hero move, the function will check if the distance is equal to
	the movespeed or smaller than the movespeed.*/
	bool IfTeammateCanMove(int movespeed, pair<int, int>current_position);/*When the teammates try to let the hero move, the function will check if the distance is equal to
	the movespeed or smaller than the movespeed.*/
	bool IfEnemyCanAttack(int range, pair<int, int>current_position);//Used in the function EnemyPlaying to check if the enemy can attack hero or the hero's teammates.
	bool IfHeroCanAttack(int range, pair<int, int>current_position);
	bool IfTeammateCanAttack(int range, pair<int, int>current_position);

	void ShowHeroMoveArea(int movespeed, pair<int, int>current_position);//Show the area the hero can move to.
	void ShowEnemyMoveArea(int movespeed, pair<int, int>current_position);//Show the area the enemy can move to.
	void ShowTeammateMoveArea(int movespeed, pair<int, int>current_position);//Show the area the teammate can move to.
	void ShowHeroAttackArea(int range, pair<int, int>current_position);//Show the area the hero can attack.
	void ShowEnemyAttackArea(int range, pair<int, int>current_position);//Show the area the enemy can attack.
	void ShowTeammateAttackArea(int range, pair<int, int>current_position);//Show the area the teammate can attack.

	void HeroMoveAreaClear();
	void HeroAttackAreaClear();

private:
	string battle_start_words = "Õ½¶·¿ªÊ¼£¡";//These words occur when the battle starts.
	map<string, string>battling_words = {};//These occur during the battle.
	string battle_end_words;//These occur at the end of the battle.
	vector<Enemy>enemies;//The vector will be changed during a battle.
	vector<Teammate>teammates;
	string cursor = "¡è";
	pair<int, int>cursor_position = {20,20};//The position of the moving cursor ¡è
	pair<int, int>battle_menu_cursor_position = { 22,9 };//The position of the cursor -> in the battle menu.
	int cursor_flashing_count = 0;//This decides whether the cursor appears or not.

	int current_enemy_index = 0;//The index of the enemy which is being used by the computer.
	int current_teammate_index = 0;//The index of the teammate which is used by the player now.

	string current_attack_type = "physics";//The type of the current attack.

	bool if_enemy_playing = false;//Computer's round.

	//When the player or the enemy chooses to attack, this will be true and the function CalculateDemage will be used.
	bool if_hero_attack_enemy = false;
	bool if_enemy_attack_hero = false;
	bool if_teammate_attack_enemy = false;
	bool if_enemy_attack_teammate = false;

	vector<Enemy>enemies_to_be_attacked;
	vector<Teammate>teammates_to_be_attacked;
	bool hero_will_be_attacked = false;

	int RestrainCheck(Enemy& enemy, Hero& hero,const string&msg);//To check whether the enemy restrains the hero or the hero restrains the enemy.
	int RestrainCheck(Enemy& enemy, Teammate&teammate, const string&msg);//To check whether the enemy restrains the teammate or the hero restrains the enemy.

	void InitializingEnemies(const string&filename);//Decide the amount and the kind of the enemies.
	void InitializingTeammates(const string&filename);////Decide the amount and the kind of the teammates.



};

#endif