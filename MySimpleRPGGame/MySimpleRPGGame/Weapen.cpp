#include"stdafx.h"

#include"Character.h"
#include"Weapen.h"
#include"FileIO.h"
#include<iostream>
#include<vector>

extern FileIO fileIO;

Weapen::Weapen(const Weapen&rhs)
{

}

void Weapen::InitializingWeapen(const string&name)
{
	this->name = name;
	this->attack = fileIO.GetWeapenData(name, "attack");
	this->endurance = fileIO.GetWeapenData(name, "endurance");
	this->hitrate = fileIO.GetWeapenData(name, "hitrate");
	this->onehit = fileIO.GetWeapenData(name, "onehit");
	this->range = fileIO.GetWeapenData(name, "range");
	this->weapen_property = fileIO.GetWeapenProperty(name);
}

Weapen& Weapen::operator=(const Weapen&rhs)
{
	this->attack = rhs.attack;
	this->endurance = rhs.endurance;
	this->hitrate = rhs.hitrate;
	this->range = rhs.range;
	this->sellingprice = rhs.sellingprice;
	this->onehit = rhs.onehit;
	return *this;
}