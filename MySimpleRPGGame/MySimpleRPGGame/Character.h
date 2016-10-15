
//The defination of the characters in this RPG game.
//The class Hero and the class Enemy both inherit from the class Character.

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<map>

#include"Weapen.h"
#include"Technique.h"


using namespace std;

class Character {//Game Character,an abstract class

	friend class Weapen;
	
public:
	string GetName()const { return name; }
	string GetStatus()const { return status; }
	void SetName(string&n) { name = n; }
	void SetStatus(string&s) { status = s; }

public:
	Character() = default;
	virtual ~Character() {};
	Character(string n) :name(n) {};//Initializing the character with name, can both used by Hero and Enemy.
	Character(const Character&);
	Character& operator=(const Character&);

	
	virtual void Move() = 0;//The hero's moving method differs from the enemy's one.
	void InitializingAbilities(string kind,int value);//To set the initial abilities
	void AddTechniques(const string&name) {};

	//
	int GetPositionX()const { return positionX; }
	int GetPositionY()const { return positionY; }
	void SetPositionX(int x) { positionX = x; };
	void SetPositionY(int y) { positionY = y; };

	int GetLevel()const { return level; }

	//The follwing things will happen during the battle.
	void Dodge();//Avoid being attacked.
	void Escape();
	void UseTechniques();
	virtual void Die() = 0;
	void ChangeAbility(const string&kind,int change);//This will change the attack,defend,magicpower,etc.
	Weapen& GetCurrentWeapen() {	return current_weapen;	}
	const Weapen& GetCurrentWeapen()const { return current_weapen; }

	int GetAbility(const string& kind)const;
	void SetBasicAbility(const string &career);//This will decide the abilities of a character of level 1.
	void AbilityCalculator(int level);//After the function SetBasicAbility() is used, this function will calculate the final abilities according to the variable "level".

private:
	//All characters possess these properities

	int positionX = 20;
	int positionY = 20;

	int attack;
	int defend;
	int magicpower;
	int fortune;
	int level;
	int life;
	int movespeed;
	int technique;
	int agility;
	string name;
	string status="Õý³£";//To see if the person is in any abnormal status or is normal.
	Weapen current_weapen;
};

class Hero :public Character {

private:
	int money;
	int exp;//The experience is related to the level of the hero.
	int techniquepoint;//This is used to update the level of the techniques.
	string image = "¡ï";
	string accomplishment;//To show what the her has achieved.
	string item;
	vector<Weapen>hero_weapens = {};
	vector<Technique>hero_techniques = {};
	vector<string>accomplishments = {};
	map<string, int>abilities = {};

	//Help print the information of the hero.
	vector<string>GetAccomplishment()const { return accomplishments; };
	vector<Weapen> GetWeapens()const { return hero_weapens; };
	vector<Technique>GetTechniques()const { return hero_techniques; };
	map<string, int>GetAbilities()const { return abilities; };

	void AddWeapens(string&weapen_name) {};


	//Rewriting the virtual methods in Character.
	void Move() override;
	void Die() override;

public:
	//Display the information of the hero.
	ostream& PrintWeapens();
	ostream& PrintAccomplishments();
	ostream& PrintAbilities();
	ostream& PrintMoney();
	ostream& PrintExp();

	//
	Hero() = default;

	//
	string GetImage()const { return image; }

	void SetExp(int e) { exp = e; }
	void SetMoney(int m) { money = m; }
	void SetTechniquePoint(int t) { techniquepoint = t; }

	int GetExp()const { return exp; }
	int GetMoney()const { return money; }
	int GetTechniquePoint()const { return techniquepoint; }

	void LevelUp() {};
};

class Enemy :public Character {

private:
	string items;//The items left by the enemies after they are defeated.
	string image ="¡ñ";
	string kind = "normal";//"normal" or "boss"


public:
	virtual void Move() {};
	virtual void Die() {}

	string GetEnemyKind() { return kind; }

	Enemy(const Enemy&rhs) :Character(rhs), items(rhs.items), image(rhs.image) {};
	Enemy& operator=(const Enemy&);
	Enemy() = default;
};

class Teammate :public Character{//Help the hero to fight against the enemies.

public:
	virtual void Move() {};
	virtual void Die() {};
};

#endif
