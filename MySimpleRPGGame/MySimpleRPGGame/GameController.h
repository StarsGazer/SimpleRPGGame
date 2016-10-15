#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include<iostream>
#include<vector>
#include"Character.h"
#include"GameScene.h"
#include<Windows.h>
#include"BattleSystem.h"

#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'
#define MENU_UP 'o'
#define MENU_DOWN 'l'
#define MENU_PRESS 'p'
#define BATTLING_MENU_APPEAR 'j'
#define BATTLING_MENU_UP 'w'
#define BATTLING_MENU_DOWN 's'
#define BATTLING_MENU_PRESS 'j'
#define TITLE_MENU_UP 'w'
#define TITLE_MENU_DOWN 's'
#define TITLE_MENU_PRESS 'j'


class GameController {

	friend class BattleSystem;

public:

	void CharacterMoving();//How the character moves
	void UsingTechniques();
	void UsingItems();
	void GoBack();
	void Continue();
	void UsingMenu();
	void UsingTitle();
	void BattlingCursorMoving();//How the cursor in the battle moves.
	void UsingBattlingMenu();
	
	GameController() = default;

	void Sethitkey(char h) { hitkey = h; }

	bool IfGameStarts() { return game_start; }

	bool IfBattleStarts() { return battle_start; }
	void SetBattleStart() { battle_start = true; }

private:

	GameScene Scene;

	char hitkey = ' ';//Get the input from the player and decide the operation.
	bool game_start = false;//If the game starts£¨The player presses the item "Game Start" or the saved data is loaded.),it will be true.
	bool battle_start = false;

	//Used in the public functions.
	void SetPosition(int x,int y);

};

#endif