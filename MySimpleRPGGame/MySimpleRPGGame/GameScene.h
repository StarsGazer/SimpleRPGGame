#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include<cstdlib>
#include<vector>
#include<iostream>
#include<map>
#include<utility>

#define WALL_WIDTH 60
#define WALL_HEIGHT 30

#define MENU_WIDTH 12
#define MENU_HEIGHT 30

#define STATUS_AREA_WIDTH 20
#define STATUS_AREA_HEIGHT 15
#define ITEMS_AREA_WIDTH 20
#define ITEMS_AREA_HEIGHT 15
#define TECHNIQUES_AREA_WIDTH 20
#define TECHNIQUES_AREA_HEIGHT 15
#define ACCOMPLISHMENTS_AREA_WIDTH 20
#define ACCOMPLISHMENTS_AREA_HEIGHT 15

#define BATTLE_MENU_AREA_OF_HERO_WIDTH 10
#define BATTLE_MENU_AREA_OF_HERO_HEIGHT 15
#define BATTLE_MENU_AREA_OF_ENEMY_WIDTH 10
#define BATTLE_MENU_AREA_OF_ENEMY_HEIGHT 3
#define BATTLE_MENU_AREA_OF_BLANK_WIDTH 10
#define BATTLE_MENU_AREA_OF_BLANK_HEIGHT 15

#define BATTLE_START_WARMING_WIDTH 10
#define BATTLE_START_WARMING_HEIGHT 5
#define BATTLE_END_INFORMATION_WIDTH 15
#define BATTLE_END_INFORMATION_HEIGHT 23

#define SELECT_SAVED_DATA_AREA_WIDTH 10
#define SELECT_SAVED_DATA_AREA_HEIGHT 15

#define MAP_WIDTH 40
#define MAP_HEIGHT 17

#define DIALOG_AREA_WIDTH 40
#define DIALOG_AREA_HEIGHT 7

#define BATTLE_PURPOSE_AREA_WIDTH 30
#define BATTLE_PURPOSE_AREA_HEIGHT 10

#define TITLE_SCENE 0
#define TOWN_SCENE 1
#define FOREST_SCENE 2
#define BATTLE_SCENE 3

using namespace std;

class GameScene {
	
private:
	char Wall[WALL_WIDTH][WALL_HEIGHT] = {};
	char Menu[MENU_WIDTH][MENU_HEIGHT] = {};
	char StatusArea[STATUS_AREA_WIDTH][STATUS_AREA_HEIGHT] = {};
	char ItemsArea[ITEMS_AREA_WIDTH][ITEMS_AREA_HEIGHT] = {};
	char TechniquesArea[TECHNIQUES_AREA_WIDTH][TECHNIQUES_AREA_HEIGHT] = {};
	char AccomplishmentArea[ACCOMPLISHMENTS_AREA_WIDTH][ACCOMPLISHMENTS_AREA_HEIGHT] = {};
	char BattleMenuOfHero[BATTLE_MENU_AREA_OF_HERO_WIDTH][BATTLE_MENU_AREA_OF_HERO_HEIGHT] = {};
	char BattleMenuOfEnemy[BATTLE_MENU_AREA_OF_ENEMY_WIDTH][BATTLE_MENU_AREA_OF_ENEMY_HEIGHT] = {};
	char BattleMenuOfBlank[BATTLE_MENU_AREA_OF_BLANK_WIDTH][BATTLE_MENU_AREA_OF_BLANK_HEIGHT] = {};
	char SelectSavedDataArea[SELECT_SAVED_DATA_AREA_WIDTH][SELECT_SAVED_DATA_AREA_HEIGHT] = {};
	char BattleStartWarming[BATTLE_START_WARMING_WIDTH][BATTLE_START_WARMING_HEIGHT] = {};
	char BattleEndInformation[BATTLE_END_INFORMATION_WIDTH][BATTLE_END_INFORMATION_HEIGHT] = {};
	char Map[MAP_WIDTH][MAP_HEIGHT] = {};
	char DialogArea[DIALOG_AREA_WIDTH][DIALOG_AREA_HEIGHT] = {};
	char BattlePurposeArea[BATTLE_PURPOSE_AREA_WIDTH][BATTLE_PURPOSE_AREA_HEIGHT] = {};

	int menu_positionX = 50;
	int menu_positionY = 2;//The position of '->'in the main menu.
	map<char,char>patterns = {};//Decide what patterns will be drawn in the scene.
	int saved_data_cursor_positionX = 38;//The position of '->' when choosing the saved data.
	int saved_data_cursor_positionY = 11;
	int title_cursor_positionX = WALL_WIDTH / 2 - 4;
	int title_cursor_positionY = 14;

	vector<pair<int, int>>fixed_characters;//The position of the fixed characters in the game
	vector<pair<int, int>>forbidden_to_move;//The position which the character can't move to

	void SetPosition(int x,int y);//Used to help draw the scene.


private:
	void DrawWalls();//Draw the walls
	void DrawMenu();//Draw the menu in town, forest and so on.

	

public:
	GameScene() = default;
	~GameScene() {};
	GameScene(int kind);//The "kind" will decide which scene to be drawn.
	void DrawScene();//Draw the whole scene.It can be used by the SceneManager() in the class named GameManager.
	void ChangeData();//Change the data in some places in a scene.
	void DrawCharacters();//Get the position of the characters and place them in the scene.


	//The followings, Get...PositionX,Y and Set...PositionX,Y will change the position of the cursor '->' in different menus;
	int GetMenuPositionX() { return menu_positionX; }
	int GetMenuPositionY() { return menu_positionY; }
	void SetMenuPositionX(int x) { menu_positionX = x; }
	void SetMenuPositionY(int y) { menu_positionY = y; }//Related to the main menu in the game.

	int GetSavedDataCursorPositionX() { return saved_data_cursor_positionX; }
	int GetSavedDataCursorPositionY() { return saved_data_cursor_positionY; }
	void SetSavedDataCursorPositionX(int x) { saved_data_cursor_positionX = x; }
	void SetSavedDataCursorPositionY(int y) { saved_data_cursor_positionY = y; }//Related to the menu of choosing the saved data.

	int GetTitleCursorPositionX() { return title_cursor_positionX; }
	int GetTitleCursorPositionY() { return title_cursor_positionY; }
	void SetTitleCursorPositionX(int x) { title_cursor_positionX = x; }
	void SetTitleCursorPositionY(int y) { title_cursor_positionY = y; }//Related to the menu in the title.

	void DrawStatusArea();//Draw the area which shows the status of the hero in the scene.
	//And the followings are same as the operations of the status area. 
	void DrawItemsArea();
	void DrawTechniquesArea();
	void DrawAccomplishmentsArea();

	void DrawBattleMenuOfHero();//Draw the menu when the hero is selected.
	void DrawBattleMenuOfEnemy();//Draw the menu when the enemy is selected.
	void DrawBattleMenuOfBlank();//Draw the menu when the blank is selected.

	void DrawBattleStartWarming();
	void DrawBattleEndInformation();
	void DrawBattleEndMovingWarming();
	void DrawBattleEndAttackingWarming();

	void DrawSelectSavedDataArea();

	void DrawMap();

	void DrawTitleScene();

	void DrawDialogWall();
	void DrawDialogWords(const string& words);//The words will be shown in the dialog.

	void DrawBattlePurpose(const string& victory,const string& failure);//Show the condition of victory and failure.

	void AreasClear();//Used to clear the area of items,status,accomplishments and techniques.
	void BattleAreasClear();
	void BattleStartWarmingClear();
	void BattleEndMovingWarmingClear();
	void BattleEndAttackingWarmingClear();
	void BattleEndInfoClear();
	void SelectSavedDataAreaClear();
	void MapClear();
	void TitleClear();
	void DialogClear();
	void DialogWordsClear();
	void BattlePurposeClear();

	void RedrawCharaters();

};

#endif //
