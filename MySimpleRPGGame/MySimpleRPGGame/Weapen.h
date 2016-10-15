#ifndef __WEAPEN_H__
#define __WEAPEN_H__

#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include"Character.h"

using namespace std;

class Weapen {
public:
	Weapen() = default;
	 ~Weapen() {};
	Weapen(const Weapen&);
	Weapen& operator=(const Weapen&);

	void ShowDetails();
	void LevelUp();
	void ChangeEdurance(string msg,int change);//The "msg" decides which way to change the endurance, add or reduce.

	int GetAttack()const { return attack; }
	int GetOnehit()const { return onehit; }
	int Gethitrate() const{ return hitrate; }
	double GetEndurance()const { return endurance; }
	int GetRange() const{ return range; }
	string GetName() const{ return name; }
	int GetLevel()const{ return level; }
	int GetSellingprice()const{ return sellingprice; }
	string GetProperty() const{ return weapen_property; }
	string GetKind()const { return weapen_kind; }

	void InitializingWeapen(const string&name);
	void WeapenAbilityCalculator(int level);

private:
	int attack;
	int onehit;//The rate to make an extremly demage
	int hitrate;//The rate of successfully hiting the character.
	double endurance;
	string name;
	string weapen_property="sword";//The property of the weapen,such as sword,axe.
	string weapen_kind="physics";//The kind of the weapen,magic or physics.It will decide the type of the attack.
	string effect;//What other effects it will cause after hiting others.
	int level;
	int sellingprice;
	int range=2;//The range of the weapen decides the max distance of the attack.

	
};



#endif // !

