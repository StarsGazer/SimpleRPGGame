#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include"GameController.h"

#include<cstdlib>
#include<iostream>
#include<vector>


class GameManager {

private:


public:
	GameManager() = default;
	~GameManager() {};
	GameScene SceneManager(int kind);//Used when a new scene occurs.

	void BattleManager();//Used when a new battle starts.
	void ControllerManager();
	void TitleManager();//Used in the title.
	void AllManager();
};

#endif 