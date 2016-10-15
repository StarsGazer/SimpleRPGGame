
//

#include "stdafx.h"
#include "Character.h"
#include"GameController.h"
#include"GameScene.h"
#include"GameManager.h"
#include"FileIO.h"

#include<Windows.h>
#include<cstdlib>
#include<conio.h>

FileIO fileIO;//Used in every cpp file.

extern Hero GameHero;

int main()
{	
	system("mode con cols=125 lines=33");

	fileIO.ReadWeapenData();
	GameHero.SetBasicAbility("swordman");

	GameManager _MyManager;
	_MyManager.AllManager();

    return 0;
}

