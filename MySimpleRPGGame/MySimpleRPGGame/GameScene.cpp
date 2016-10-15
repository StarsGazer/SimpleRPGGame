#include"stdafx.h"

#include"GameScene.h"
#include<iostream>
#include"Character.h"
#include<Windows.h>
#include<vector>
#include"BattleSystem.h"
#include"MapSystem.h"


using std::cout;
extern Hero GameHero;
extern BattleSystem Battle;


void GameScene::SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

GameScene::GameScene(int kind) 
{

	switch (kind)
	{
	case TITLE_SCENE: {
		patterns.insert({ '->','->' });
		patterns.insert({ '<-','<-' });
		patterns.insert({ 'e',TITLE_SCENE });
	}
	case TOWN_SCENE: {
		patterns.insert({ '■','■' });
		patterns.insert({ '->','->' });
		patterns.insert({'<-','<-'});
		patterns.insert({ 'e',TOWN_SCENE });//'e' means the end of the map
	}break;
	case FOREST_SCENE: {

	}break;
	case BATTLE_SCENE: {
		patterns.insert({ '●','●' });
		patterns.insert({ '->','->' });
		patterns.insert({ '<-','<-' });
		patterns.insert({ 'e',BATTLE_SCENE });
	}break;
	default:break;
	}; 

}

void GameScene::DrawScene() 
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });

	switch (patterns['e'])
	{

	case TITLE_SCENE: 
	{
		DrawWalls();
		DrawTitleScene();
	}break;
	case TOWN_SCENE: 
	{
		DrawWalls();
		DrawMenu();
	}
	break;
	case FOREST_SCENE:
	{
		
	}
		break;
	case BATTLE_SCENE:
	{
		DrawWalls();
		DrawBattleStartWarming();
		BattleStartWarmingClear();
	}break;
	default:
		break;
	}

	//The followings are prepared for the next scene.
	patterns.clear();
}

void GameScene::DrawMenu()//Draw the menu in a scene
{
	int i = 0, j = 0;
	for (i = 0; i != MENU_WIDTH;++i)
	{
		for (j = 1; j != MENU_HEIGHT-1; ++j)
		{
			if (j == 1 || j == MENU_HEIGHT - 15)
				Menu[i][j] = '-';
			else if (i == 1 || i == MENU_WIDTH - 1)
				Menu[i][j] = '|';
		}
	}
	for (i = 1; i != MENU_WIDTH; ++i)
	{
		for (j = 1; j != MENU_HEIGHT; ++j)
		{
			if (Menu[i][j] == '|')
			{
				SetPosition(i+48, j);
				cout << patterns['|'] << flush;
			}
			else if (Menu[i][j] == '-') 
			{
				SetPosition(i+48, j);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}

	SetPosition(52, 2);
	cout << "主角状态" <<flush;
	SetPosition(52, 4);
	cout << "道具和装备" << flush;
	SetPosition(52, 6);
	cout << "技能信息" << flush;
	SetPosition(52, 8);
	cout << "游戏地图" << flush;
	SetPosition(52, 10);
	cout << "查看成就" << flush;
	SetPosition(52, 12);
	cout << "存档" << flush;
	SetPosition(52, 14);
	cout << "读档" << flush;
	SetPosition(GetMenuPositionX(),GetMenuPositionY());
	cout << "->"<< flush;

}

void GameScene::DrawWalls()//Draw the walls in a scene.
{
	int i = 0, j = 0;
	for (i = 1; i != WALL_WIDTH; ++i)
	{
		for (j = 1; j != WALL_HEIGHT; ++j)
		{
			if (j == 1 || j == WALL_HEIGHT - 1)
				Wall[i][j] = '-';
			else if (i == 1 || i == WALL_WIDTH - 1)
				Wall[i][j] = '|';
		}
	}
	for (i = 1; i != WALL_WIDTH; ++i)
	{
		for (j = 1; j != WALL_HEIGHT; ++j)
		{
			if (Wall[i][j] == '|')
			{
				SetPosition(i, j);
				cout << patterns['|'] << flush;
			}
			else if (Wall[i][j] == '-') {
				SetPosition(i, j);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
}

void GameScene::DrawStatusArea()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != STATUS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != STATUS_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == STATUS_AREA_HEIGHT - 1)
				StatusArea[i][j] = '-';
			else if (i == 1 || i == STATUS_AREA_WIDTH - 1)
				StatusArea[i][j] = '|';
		}
	}
	for (i = 1; i != STATUS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != STATUS_AREA_HEIGHT; ++j)
		{
			if (StatusArea[i][j] == '|')
			{
				SetPosition(i+10, j+5);
				cout << patterns['|'] << flush;
			}
			else if (StatusArea[i][j] == '-') 
			{
				SetPosition(i+10, j+5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}

	SetPosition(14, 7);
	cout << "名字:" << GameHero.GetName() << flush;
	SetPosition(22, 7);
	cout << "等级:" << GameHero.GetLevel() << flush;
	SetPosition(14, 9);
	cout << "力量:" << GameHero.GetAbility("attack") << flush;
	SetPosition(14, 11);
	cout << "防守:" << GameHero.GetAbility("defend") << flush;
	SetPosition(14, 13);
	cout << "魔力:" << GameHero.GetAbility("magicpower") << flush;
	SetPosition(14, 15);
	cout << "运气:" << GameHero.GetAbility("fortune") << flush;
	SetPosition(14, 17);
	cout << "速度:" << GameHero.GetAbility("movespeed") << flush;
	SetPosition(22, 9);
	cout << "生命:" << GameHero.GetAbility("life") << flush;
	SetPosition(22, 11);
	cout << "敏捷:" << GameHero.GetAbility("agility") << flush;
	SetPosition(22, 13);
	cout << "状态:" << GameHero.GetStatus() << flush;
	SetPosition(22, 15);
	cout << "经验值:" << GameHero.GetExp() << flush;
	SetPosition(22, 17);
	cout << "金钱:" << GameHero.GetMoney() << flush;
}

void GameScene::DrawItemsArea()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != ITEMS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != ITEMS_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == ITEMS_AREA_HEIGHT - 1)
				ItemsArea[i][j] = '-';
			else if (i == 1 || i == ITEMS_AREA_WIDTH - 1)
				ItemsArea[i][j] = '|';
		}
	}
	for (i = 1; i != ITEMS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != ITEMS_AREA_HEIGHT; ++j)
		{
			if (ItemsArea[i][j] == '|')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (ItemsArea[i][j] == '-') 
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(18,7);
	cout << "道具列表" << flush;
	//Get the list of the items and then show them in the menu.

}


void GameScene::DrawTechniquesArea()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != TECHNIQUES_AREA_WIDTH; ++i)
	{
		for (j = 1; j != TECHNIQUES_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == TECHNIQUES_AREA_HEIGHT - 1)
				TechniquesArea[i][j] = '-';
			else if (i == 1 || i == TECHNIQUES_AREA_WIDTH - 1)
				TechniquesArea[i][j] = '|';
		}
	}
	for (i = 1; i != TECHNIQUES_AREA_WIDTH; ++i)
	{
		for (j = 1; j != TECHNIQUES_AREA_HEIGHT; ++j)
		{
			if (TechniquesArea[i][j] == '|')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (TechniquesArea[i][j] == '-')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}

	SetPosition(18, 7);
	cout << "技能列表" << flush;

}



void GameScene::DrawAccomplishmentsArea()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != ACCOMPLISHMENTS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != ACCOMPLISHMENTS_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == ACCOMPLISHMENTS_AREA_HEIGHT - 1)
				AccomplishmentArea[i][j] = '-';
			else if (i == 1 || i == ACCOMPLISHMENTS_AREA_WIDTH - 1)
				AccomplishmentArea[i][j] = '|';
		}
	}
	for (i = 1; i != ACCOMPLISHMENTS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != ACCOMPLISHMENTS_AREA_HEIGHT; ++j)
		{
			if (AccomplishmentArea[i][j] == '|')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (AccomplishmentArea[i][j] == '-')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}

	SetPosition(18,7);
	cout << "成就列表" << flush;
}

void GameScene::AreasClear()
{
	int i = 0, j = 0;

	for (i = 1; i != STATUS_AREA_WIDTH; ++i)
	{
		for (j = 1; j != STATUS_AREA_HEIGHT; ++j)
		{
			SetPosition(i + 10, j + 5);
			cout << "  " << flush;
		}
		cout << endl;
	}
}

void GameScene::DrawBattleMenuOfHero()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_MENU_AREA_OF_HERO_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_HERO_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_MENU_AREA_OF_HERO_HEIGHT - 1)
				BattleMenuOfHero[i][j] = '-';
			else if (i == 1 || i == BATTLE_MENU_AREA_OF_HERO_WIDTH - 1)
				BattleMenuOfHero[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_MENU_AREA_OF_HERO_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_HERO_HEIGHT; ++j)
		{
			if (BattleMenuOfHero[i][j] == '|')
			{
				SetPosition(i + 20, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (BattleMenuOfHero[i][j] == '-')
			{
				SetPosition(i + 20, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(23, 10);
	cout << "移动" << flush;
	SetPosition(23, 12);
	cout << "进攻" << flush;
	SetPosition(23, 14);
	cout << "主角能力" << flush;
	SetPosition(23, 16);
	cout << "返回游戏" << flush;

}

void GameScene::DrawBattleMenuOfEnemy()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_MENU_AREA_OF_ENEMY_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_ENEMY_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_MENU_AREA_OF_ENEMY_HEIGHT - 1)
				BattleMenuOfEnemy[i][j] = '-';
			else if (i == 1 || i == BATTLE_MENU_AREA_OF_ENEMY_WIDTH - 1)
				BattleMenuOfEnemy[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_MENU_AREA_OF_ENEMY_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_ENEMY_HEIGHT; ++j)
		{
			if (BattleMenuOfEnemy[i][j] == '|')
			{
				SetPosition(i + 20, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (BattleMenuOfEnemy[i][j] == '-')
			{
				SetPosition(i + 20, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(22, 10);
	cout << "能力" << flush;
}

void GameScene::DrawBattleMenuOfBlank()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_MENU_AREA_OF_BLANK_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_BLANK_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_MENU_AREA_OF_BLANK_HEIGHT - 1)
				BattleMenuOfBlank[i][j] = '-';
			else if (i == 1 || i == BATTLE_MENU_AREA_OF_BLANK_WIDTH - 1)
				BattleMenuOfBlank[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_MENU_AREA_OF_BLANK_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_BLANK_HEIGHT; ++j)
		{
			if (BattleMenuOfBlank[i][j] == '|')
			{
				SetPosition(i + 20, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (BattleMenuOfBlank[i][j] == '-')
			{
				SetPosition(i + 20, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(23, 9);
	cout << "结束本回合" << flush;
	SetPosition(23, 11);
	cout << "己方信息" << flush;
	SetPosition(23, 13);
	cout << "敌方信息" << flush;
	SetPosition(23, 15);
	cout << "作战目的" << flush;
	SetPosition(23, 17);
	cout << "返回游戏" << flush;

}

void GameScene::BattleAreasClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_MENU_AREA_OF_BLANK_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_MENU_AREA_OF_BLANK_HEIGHT; ++j)
		{
			SetPosition(i + 20, j + 5);
			cout << "  " << flush;
		}
	}
}

void GameScene::DrawSelectSavedDataArea()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != SELECT_SAVED_DATA_AREA_WIDTH; ++i)
	{
		for (j = 1; j != SELECT_SAVED_DATA_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == SELECT_SAVED_DATA_AREA_HEIGHT - 1)
				SelectSavedDataArea[i][j] = '-';
			else if (i == 1 || i == SELECT_SAVED_DATA_AREA_WIDTH - 1)
				SelectSavedDataArea[i][j] = '|';
		}
	}
	for (i = 1; i != SELECT_SAVED_DATA_AREA_WIDTH; ++i)
	{
		for (j = 1; j != SELECT_SAVED_DATA_AREA_HEIGHT; ++j)
		{
			if (SelectSavedDataArea[i][j] == '|')
			{
				SetPosition(i + 35, j + 8);
				cout << patterns['|'] << flush;
			}
			else if (SelectSavedDataArea[i][j] == '-')
			{
				SetPosition(i + 35, j + 8);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(40, 11);
	cout << "存档1" << flush;
	SetPosition(40, 12);
	cout << "存档2" << flush;
	SetPosition(40, 13);
	cout << "存档3" << flush;
	SetPosition(40, 14);
	cout << "存档4" << flush;
	SetPosition(40, 15);
	cout << "存档5" << flush;
	SetPosition(40, 16);
	cout << "存档6" << flush;
	SetPosition(40, 17);
	cout << "存档7" << flush;
	SetPosition(40, 18);
	cout << "存档8" << flush;
	SetPosition(40, 19);
	cout << "存档9" << flush;
	SetPosition(40, 20);
	cout << "存档10" << flush;

}

void GameScene::SelectSavedDataAreaClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != SELECT_SAVED_DATA_AREA_WIDTH; ++i)
	{
		for (j = 1; j != SELECT_SAVED_DATA_AREA_HEIGHT; ++j)
		{
			SetPosition(i + 35, j + 8);
			cout << "  " << flush;
		}
	}
}

void GameScene::DrawMap()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != MAP_WIDTH; ++i)
	{
		for (j = 1; j != MAP_HEIGHT; ++j)
		{
			if (j == 1 || j == MAP_HEIGHT - 1)
				Map[i][j] = '-';
			else if (i == 1 || i == MAP_WIDTH - 1)
				Map[i][j] = '|';
		}
	}
	for (i = 1; i != MAP_WIDTH; ++i)
	{
		for (j = 1; j != MAP_HEIGHT; ++j)
		{
			if (Map[i][j] == '|')
			{
				SetPosition(i + 5, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (Map[i][j] == '-')
			{
				SetPosition(i + 5, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}

	MapSystem Map;
	for (int k = 0; k != Map.GetPlacesLength(); ++k)
	{
		SetPosition(Map.GetPlacePositionXAtIndex(k), Map.GetPlacePositionYAtIndex(k));
		cout << patterns['■'] << flush;//Draw the important places such as town or forest in the map.

	}

}

void GameScene::MapClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != MAP_WIDTH; ++i)
	{
		for (j = 1; j != MAP_HEIGHT; ++j)
		{
			SetPosition(i + 5, j + 5);
			cout <<" " << flush;
		}
		cout << endl;
	}
}

void GameScene::DrawBattleStartWarming()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j !=BATTLE_START_WARMING_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_START_WARMING_HEIGHT - 1)
				BattleStartWarming[i][j] = '-';
			else if (i == 1 || i == BATTLE_START_WARMING_WIDTH - 1)
				BattleStartWarming[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			if (BattleStartWarming[i][j] == '|')
			{
				SetPosition(i + 20, j + 10);
				cout << patterns['|'] << flush;
			}
			else if (BattleStartWarming[i][j] == '-')
			{
				SetPosition(i + 20, j + 10);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(23, 12);
	cout << "战斗开始！" << flush;
	Sleep(2000);
}

void GameScene::DrawBattleEndInformation()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_END_INFORMATION_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_END_INFORMATION_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_END_INFORMATION_HEIGHT - 1)
				BattleEndInformation[i][j] = '-';
			else if (i == 1 || i == BATTLE_END_INFORMATION_WIDTH - 1)
				BattleEndInformation[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_END_INFORMATION_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_END_INFORMATION_HEIGHT; ++j)
		{
			if (BattleEndInformation[i][j] == '|')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['|'] << flush;
			}
			else if (BattleEndInformation[i][j] == '-')
			{
				SetPosition(i + 10, j + 5);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
}

void GameScene::DrawBattleEndMovingWarming()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_START_WARMING_HEIGHT - 1)
				BattleStartWarming[i][j] = '-';
			else if (i == 1 || i == BATTLE_START_WARMING_WIDTH - 1)
				BattleStartWarming[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			if (BattleStartWarming[i][j] == '|')
			{
				SetPosition(i + 20, j + 10);
				cout << patterns['|'] << flush;
			}
			else if (BattleStartWarming[i][j] == '-')
			{
				SetPosition(i + 20, j + 10);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(23, 12);
	cout << "确定移动?" << flush;
	SetPosition(22, 13);
	cout << "是(按J)否(按K)" << flush;
}

void GameScene::DrawBattleEndAttackingWarming()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_START_WARMING_HEIGHT - 1)
				BattleStartWarming[i][j] = '-';
			else if (i == 1 || i == BATTLE_START_WARMING_WIDTH - 1)
				BattleStartWarming[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			if (BattleStartWarming[i][j] == '|')
			{
				SetPosition(i + 20, j + 10);
				cout << patterns['|'] << flush;
			}
			else if (BattleStartWarming[i][j] == '-')
			{
				SetPosition(i + 20, j + 10);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(23, 12);
	cout << "确定攻击?" << flush;
	SetPosition(22, 13);
	cout << "是(按J)否(按K)" << flush;
}

void GameScene::BattleStartWarmingClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			SetPosition(i + 20, j + 10);
			cout << " " << flush;
		}
	}
}

void GameScene::BattleEndMovingWarmingClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			SetPosition(i + 20, j + 10);
			cout << "  " << flush;
		}
	}
}

void GameScene::BattleEndAttackingWarmingClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_START_WARMING_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_START_WARMING_HEIGHT; ++j)
		{
			SetPosition(i + 20, j + 10);
			cout << "  " << flush;
		}
	}
}

void GameScene::BattleEndInfoClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_END_INFORMATION_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_END_INFORMATION_HEIGHT; ++j)
		{
			SetPosition(i + 10, j + 5);
			cout << " " << flush;
		}
	}
}

void GameScene::DrawTitleScene()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	SetPosition(WALL_WIDTH / 2 - 2, 14);
	cout << "从头开始" << flush;
	SetPosition(WALL_WIDTH / 2 - 2, 16);
	cout << "读取存档" << flush;
	SetPosition(WALL_WIDTH / 2 - 2, 18);
	cout << "游戏说明" << flush;
	SetPosition(WALL_WIDTH / 2 - 2, 20);
	cout << "退出游戏" << flush;
	SetPosition(GetTitleCursorPositionX(), GetTitleCursorPositionY());
	cout << "->" << flush;
}

void GameScene::TitleClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	SetPosition(WALL_WIDTH / 2 - 6, 14);
	cout << "                " << flush;
	SetPosition(WALL_WIDTH / 2 - 6, 16);
	cout << "                " << flush;
	SetPosition(WALL_WIDTH / 2 - 6, 18);
	cout << "                " << flush;
	SetPosition(WALL_WIDTH / 2 - 6, 20);
	cout << "                " << flush;
}

void GameScene::DrawDialogWall()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != DIALOG_AREA_WIDTH; ++i)
	{
		for (j = 1; j !=DIALOG_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == DIALOG_AREA_HEIGHT - 1)
				DialogArea[i][j] = '-';
			else if (i == 1 || i == DIALOG_AREA_WIDTH - 1)
				DialogArea[i][j] = '|';
		}
	}
	for (i = 1; i !=DIALOG_AREA_WIDTH; ++i)
	{
		for (j = 1; j != DIALOG_AREA_HEIGHT; ++j)
		{
			if (DialogArea[i][j] == '|')
			{
				SetPosition(i + 6, j +22 );
				cout << patterns['|'] << flush;
			}
			else if (DialogArea[i][j] == '-')
			{
				SetPosition(i + 6, j + 22);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
}

void GameScene::DrawDialogWords(const string& words)
{
	SetPosition(14, 25);
	cout<<words<<flush;
}

void GameScene::DialogClear()
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i != DIALOG_AREA_WIDTH; ++i)
	{
		for (j = 1; j != DIALOG_AREA_HEIGHT; ++j)
		{
			SetPosition(i + 6, j + 22);
			cout << "  " << flush;
		}
	}
	
}

void GameScene::DialogWordsClear()
{
	int i = 0;
	for (i = 1; i != DIALOG_AREA_WIDTH - 1; ++i)
	{
		SetPosition(i + 13, 25);
		cout << " " << flush;
	}
}



void GameScene::DrawBattlePurpose(const string& victory, const string& failure)
{
	patterns.insert({ '|','|' });
	patterns.insert({ '-','-' });
	int i = 0, j = 0;
	for (i = 1; i !=BATTLE_PURPOSE_AREA_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_PURPOSE_AREA_HEIGHT; ++j)
		{
			if (j == 1 || j == BATTLE_PURPOSE_AREA_HEIGHT - 1)
				BattlePurposeArea[i][j] = '-';
			else if (i == 1 || i == BATTLE_PURPOSE_AREA_WIDTH - 1)
				BattlePurposeArea[i][j] = '|';
		}
	}
	for (i = 1; i != BATTLE_PURPOSE_AREA_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_PURPOSE_AREA_HEIGHT; ++j)
		{
			if (BattlePurposeArea[i][j] == '|')
			{
				SetPosition(i + 10, j + 6);
				cout << patterns['|'] << flush;
			}
			else if (BattlePurposeArea[i][j] == '-')
			{
				SetPosition(i + 10, j + 6);
				cout << patterns['-'] << flush;
			}
		}
		cout << endl;
	}
	SetPosition(12, 9);
	cout << "作战目的:" << flush;
	SetPosition(12, 11);
	cout << "胜利条件:" <<victory<<flush;
	SetPosition(12, 13);
	cout << "失败条件:" << failure<<flush;
}

void GameScene::BattlePurposeClear()
{
	int i = 0, j = 0;
	for (i = 1; i != BATTLE_PURPOSE_AREA_WIDTH; ++i)
	{
		for (j = 1; j != BATTLE_PURPOSE_AREA_HEIGHT; ++j)
		{
			SetPosition(i + 10,j + 6);
			cout << " " << flush;
		}
	}
}

void GameScene::RedrawCharaters()
{
	SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
	cout << GameHero.GetImage() << flush;
	for (size_t i = 0; i != Battle.GetEnemyAmount(); ++i)
	{
		SetPosition(Battle.GetEnemyAtIndex(i).GetPositionX(), Battle.GetEnemyAtIndex(i).GetPositionY());
		cout << "●" << flush;
	}
	for (size_t i= 0; i != Battle.GetTeammateAmount(); ++i)
	{
		SetPosition(Battle.GetTeammateAtIndex(i).GetPositionX(), Battle.GetTeammateAtIndex(i).GetPositionY());
		cout << "●" << flush;
	}
}