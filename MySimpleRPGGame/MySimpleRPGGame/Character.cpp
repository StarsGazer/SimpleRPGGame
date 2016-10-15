
#include"stdafx.h"

#include"Character.h"
#include"GameController.h"
#include<iostream>
#include<vector>

extern Hero GameHero;

int Character::GetAbility(const string& kind)const
{
	if (kind == "attack")
		return attack;
	else if (kind == "defend")
		return defend;
	else if (kind == "magicpower")
		return magicpower;
	else if (kind == "fortune")
		return fortune;
	else if (kind =="agility")
		return agility;
	else if (kind == "technique")
		return technique;
	else if (kind == "movespeed")
		return movespeed;
	else if (kind == "life")
		return life;
}

void Character::Dodge()//Avoid being attacked.
{

}

void Character::Escape()
{

}

void Character::ChangeAbility(const string&kind,int change)
{
	//This will change the ability of a character,and the number will depend on variable "change"
	if (kind == "attack")
		this->attack += change;
	else if (kind == "defend")
		this->defend+=change;
	else if (kind == "magicpower")
		this->magicpower+=change;
	else if (kind == "fortune")
		this->fortune+=change;
	else if (kind == "agility")
		this->agility+=change;
	else if (kind == "technique")
		this->technique+=change;
	else if (kind == "movespeed")
		this->movespeed+=change;  
	else if (kind == "life")
		this->life+=change;
}

void Character::UseTechniques()
{

}

Character::Character(const Character&rhs)
{
	this->name = rhs.name;
	this->attack = rhs.attack;
	this->defend = rhs.defend;
	this->agility = rhs.agility;
	this->technique = rhs.technique;
	this->current_weapen = rhs.current_weapen;
	this->level = rhs.level;
	this->magicpower = rhs.magicpower;
	this->fortune = rhs.fortune;
	this->life = rhs.life;
	this->movespeed = rhs.movespeed;
	this->positionX = rhs.positionX;
	this->positionY = rhs.positionY;
	this->status = rhs.status;
}

Character& Character::operator=(const Character&rhs)
{
	this->name = rhs.name;
	this->attack = rhs.attack;
	this->defend = rhs.defend;
	this->agility = rhs.agility;
	this->technique = rhs.technique;
	this->current_weapen = rhs.current_weapen;
	this->level = rhs.level;
	this->magicpower = rhs.magicpower;
	this->fortune = rhs.fortune;
	this->life = rhs.life;
	this->movespeed = rhs.movespeed;
	this->positionX = rhs.positionX;
	this->positionY = rhs.positionY;
	this->status = rhs.status;
	return *this;
}

Enemy& Enemy::operator=(const Enemy&rhs)
{
	Character::operator=(rhs);
	items = rhs.items;
	image = rhs.image;
	return *this;
}


void Character::InitializingAbilities(string kind,int value)//Used in FileIO.
{
	if (kind == "Life")
		GameHero.life = value;
	else if (kind == "Attack")
		GameHero.attack = value;
	else if (kind == "Defend")
		GameHero.defend = value;
	else if (kind == "MagicPower")
		GameHero.magicpower = value;
	else if (kind == "Fortune")
		GameHero.fortune = value;
	else if (kind == "Level")
		GameHero.level = value;
	else if (kind == "Technique")
		GameHero.technique = value;
	else if (kind == "MoveSpeed")
		GameHero.agility = value;
	else if (kind == "Exp")
		GameHero.SetExp(value);
	else if (kind == "Money")
		GameHero.SetMoney(value);
	else if (kind == "TechniquePoint")
		GameHero.SetTechniquePoint(value);
}

void Character::SetBasicAbility(const string& career)
{
	if (career == "swordman")
	{
		this->attack = 10;
		this->defend = 3;
		this->magicpower = 3;
		this->agility = 8;
		this->technique = 4;
		this->fortune = 3;
		this->life = 55;
		this->movespeed = 5;
	}
	else if (career == "axeman")
	{
		this->attack = 12;
		this->defend = 3;
		this->magicpower = 0;
		this->agility = 6;
		this->technique = 3;
		this->fortune = 2;
		this->life = 50;
		this->movespeed = 4;
	}
	else if (career == "archer")
	{
		this->attack = 6;
		this->defend = 1;
		this->magicpower = 2;
		this->agility = 9;
		this->technique = 4;
		this->fortune = 2;
		this->life = 40;
		this->movespeed = 5;
	}
	else if (career == "knight")
	{
		this->attack = 10;
		this->defend = 4;
		this->magicpower = 3;
		this->agility = 7;
		this->technique = 4;
		this->fortune = 1;
		this->life = 60;
		this->movespeed = 6;
	}
	else if (career == "wizard")
	{
		this->attack = 0;
		this->defend = 1;
		this->magicpower = 8;
		this->agility = 7;
		this->technique = 5;
		this->fortune = 2;
		this->life = 40;
		this->movespeed = 5;
	}
}

void Character::AbilityCalculator(int level)
{

}

void Hero::Move()
{

}

void Hero::Die()
{

}
