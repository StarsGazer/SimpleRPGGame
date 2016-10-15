#ifndef __TECHNIQUE_H__
#define __TECHNIQUE_H__

#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<utility>

using std::string;
using std::pair;

class Technique {
public:
	virtual ~Technique() {};
	Technique() = default;
	Technique(const Technique&);
	
	virtual void ShowDetails();
	virtual void LevelUp();
	void Frozen();

protected:
	int level;
	string kind;
	char key;//Press the key to use the technique.
	int requiredmp;//The magicpower consumed after using the technique.
	string name;
	pair<int, int>range;
	int frozentime;

private:


};

class PhysicsAttackTechnique: public Technique {
private:
	int physicsdemage;
	string effect;

};

class MagicAttackTechnique: public Technique {
private:
	int magicdemage;
	string effect;

};

class OtherTechniques: public Technique {
public:

private:
	string result;
};

#endif // !
