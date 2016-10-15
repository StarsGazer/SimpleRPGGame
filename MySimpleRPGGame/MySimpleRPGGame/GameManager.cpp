#include "stdafx.h"

#include"GameManager.h"
#include"GameScene.h"
#include"MapSystem.h"
#include"BattleSystem.h"
#include"Technique.h"
#include"Weapen.h"
#include"GameController.h"

#include<conio.h>

GameController MyController;
BattleSystem Battle;

GameScene GameManager::SceneManager(int kind)
{
	GameScene _MyScene(kind);//The kind decides which kind of scene to be drawn.
	return _MyScene;
}

void GameManager::TitleManager()
{
	if (_kbhit())
	{
		char hit = _getch();
		MyController.Sethitkey(hit);//This will change the "hitkey" and decide the following operations.
		MyController.UsingTitle();
	}
}

void GameManager::ControllerManager()
{
	if (_kbhit())
	{
		char hit = _getch();
		MyController.Sethitkey(hit);
		MyController.CharacterMoving();
		MyController.UsingMenu();
	}
}

void GameManager::BattleManager()
{
	if (_kbhit())
	{
		if (!Battle.IfEnemyPlaying())
		{
			char hit = _getch();//Player's round.
			MyController.Sethitkey(hit);
			MyController.BattlingCursorMoving();
			MyController.UsingBattlingMenu();
		}
		else
		{
			Battle.EnemyPlaying();//Computer's round.
		}
	}
}

void GameManager::AllManager()
//This manager will decide the whole game's process.
{
	//First,the title.
	SceneManager(TITLE_SCENE).DrawScene();
	while (!MyController.IfGameStarts())
	{
		TitleManager();
	}

	//Then based on the choice of the player, the game will load the saved data or start without the saved data.
	SceneManager(TOWN_SCENE).DrawScene();
	GameScene::GameScene().DrawDialogWall();
	GameScene::GameScene().DrawDialogWords("∂‘ª∞øÚ≤‚ ‘ abcdefg 123456789");
	while (1)
	{
		while (!MyController.IfBattleStarts())
		{
			ControllerManager();
		}
		SceneManager(BATTLE_SCENE).DrawScene();
		Battle.BattleStart("test");//Some necessary things should be done before the battle such as initializing the information of enemies.
		while (MyController.IfBattleStarts())
		{
			BattleManager();//GameController's function,related to the operation of the player.
			Battle.Battling();//Some necessary calculation will be done such as calculating demage.
			Battle.CursorFlashing();//The cursor keep flashing.
		}
		//Battle is over,IfBattleStarts should return false.
		Battle.BattleOver();
	}
}