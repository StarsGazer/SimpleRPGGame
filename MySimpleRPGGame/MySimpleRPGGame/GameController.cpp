#include"stdafx.h"

#include"GameController.h"
#include"Character.h"
#include"BattleSystem.h"
#include"MapSystem.h"
#include"GameScene.h"
#include"FileIO.h"
#include<iostream>
#include<vector>
#include<Windows.h>
#include<conio.h>
#include<cctype>
#include<ctime>

using std::cout;

Hero GameHero;//The character that will be controlled to move.
extern FileIO fileIO;
extern BattleSystem Battle;
extern bool if_hero_can_move;//Used in IfHeroCanMove().
extern bool if_enemy_can_move;//Used in IfEnemyCanMove().
extern bool if_teammate_can_move;//Used in IfTeammateCanMove().
extern bool if_hero_can_attack;//Used in IfHeroCanAttack().
extern bool if_teammate_can_attack;//Used in IfTeammateCanAttack().

void GameController::SetPosition(int x, int y) 
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	//The character will move to (x.y).
}

void GameController::CharacterMoving() 
{
	//The function used to make the character move by w,a,s,d.
	string heroImage=GameHero.GetImage();

	SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
	cout << " " << endl;
	SetPosition(62, 10);
	cout << "  " << flush;

	switch (tolower(hitkey))
		{
		case MOVE_UP:
		{
			GameHero.SetPositionY(GameHero.GetPositionY() - 1); 
			SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
		} break;
		case MOVE_DOWN: 
		{
			GameHero.SetPositionY(GameHero.GetPositionY() +1); 
			SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
		} break;
		case MOVE_LEFT:
		{
			GameHero.SetPositionX(GameHero.GetPositionX() - 1);
			SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
		}break;
		case MOVE_RIGHT:
		{
			GameHero.SetPositionX(GameHero.GetPositionX() + 1);
			SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
		} break;
		default:
		SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
		break;
		}

	cout << heroImage << flush;

}

void GameController::UsingTitle()
{
	//Press W,S to select the menuitem.
	//Press J to use the menuitem.
	SetPosition(62, 20);
	cout << "  " << flush;


	switch (hitkey)
	{
	case TITLE_MENU_UP: {//Move the '->' up.
		if (Scene.GetTitleCursorPositionY() >= 16)
		{
			SetPosition(Scene.GetTitleCursorPositionX(), Scene.GetTitleCursorPositionY());
			cout << "  " << flush;
			Scene.SetTitleCursorPositionY(Scene.GetTitleCursorPositionY() - 2);
		}; break;
	}
	case TITLE_MENU_DOWN: {//Move the '->' down.
		if (Scene.GetTitleCursorPositionY() <= 18)
		{
			SetPosition(Scene.GetTitleCursorPositionX(), Scene.GetTitleCursorPositionY());
			cout << "  " << flush;
			Scene.SetTitleCursorPositionY(Scene.GetTitleCursorPositionY() + 2);
		}; break;
	}
	case TITLE_MENU_PRESS: {
		switch (Scene.GetTitleCursorPositionY())
		{
		case 14: {
			Scene.TitleClear();
			game_start = true;
		}; break;
		case 16: {
			Scene.DrawSelectSavedDataArea();
			SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
			cout << "->" << flush;
			//The followings are the operations of reading the saved data.
			while (1)
			{
				if (_kbhit())
				{
					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.SelectSavedDataAreaClear();
						break;
					}

					switch (tolower(hitkey))
					{
					case TITLE_MENU_UP: {
						if (Scene.GetSavedDataCursorPositionY() >= 12)
						{
							SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
							cout << "  " << flush;
							Scene.SetSavedDataCursorPositionY(Scene.GetSavedDataCursorPositionY() - 1);
						}
					}break;
					case TITLE_MENU_DOWN: {
						if (Scene.GetSavedDataCursorPositionY() <= 19)
						{
							SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
							cout << "  " << flush;
							Scene.SetSavedDataCursorPositionY(Scene.GetSavedDataCursorPositionY() + 1);
						}
					}break;
					case TITLE_MENU_PRESS: {
						//The class FileIO will start to work here.
						switch (Scene.GetSavedDataCursorPositionY())//The cursor's y position will decide which data to be changed.
						{
						case 11: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata1.txt"); //Then the important information in the game will be initialized.

						}break;
						case 12: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata2.txt");
						}break;
						case 13: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata3.txt");
						}break;
						case 14: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata4.txt");
						}break;
						case 15: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata5.txt");
						}break;
						case 16: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata6.txt");
						}break;
						case 17: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata7.txt");
						}break;
						case 18: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata8.txt");
						}break;
						case 19: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata9.txt");
						}break;
						case 20: {
							FileIO fileIO;
							fileIO.ReadSavedData("saveddata10.txt");
						}break;
						}
					}break;
					}
					SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
					cout << "->" << flush;
				}
			}
		}; break;
		case 18: {
		}; break;
		case 20:exit(0); break;
		}
	}break;
	default:
		break;
	}
	if (!game_start)//Avoid drawing '->' in the scene again when the game starts.
	{
		SetPosition(Scene.GetTitleCursorPositionX(), Scene.GetTitleCursorPositionY());
		cout << "->" << flush;
	}
}

void GameController::UsingMenu()
{
	//Press O,L to select the menuitem. 
	//Press P to use the menuitem.
	SetPosition(62, 20);
	cout << "  " << flush;

	switch (hitkey)
	{
	case MENU_UP: {//Move the '->' up.
		if (Scene.GetMenuPositionY() >= 4)
		{
			SetPosition(Scene.GetMenuPositionX(), Scene.GetMenuPositionY());
			cout << "  " << flush;
			Scene.SetMenuPositionY(Scene.GetMenuPositionY() - 2);
		}
	}; break;
	case MENU_DOWN: {//Move the '->' down.
		if (Scene.GetMenuPositionY() <= 12)
		{
			SetPosition(Scene.GetMenuPositionX(), Scene.GetMenuPositionY());
			cout << "  " << flush;
			Scene.SetMenuPositionY(Scene.GetMenuPositionY() + 2);
		}
	}; break;
	case MENU_PRESS: {
		switch (Scene.GetMenuPositionY())
		{
		case 2: {
			Scene.DrawStatusArea();
			while (1)
			{
				if (_kbhit())
				{
					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.AreasClear();
						Scene.RedrawCharaters();
						break;
					}
				}
			}
		}; break;
		case 4: {
			Scene.DrawItemsArea();
			while (1)
			{
				if (_kbhit())
				{
					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.AreasClear();
						Scene.RedrawCharaters();
						break;
					}
				}
			}
		}; break;
		case 6: {
				Scene.DrawTechniquesArea();
				while (1)
				{
					if (_kbhit())
					{
						hitkey = _getch();
						if (hitkey == 'k')
						{
							Scene.AreasClear();
							Scene.RedrawCharaters();
							break;
						}
					}
				}
		}break;
		case 8: {
			Scene.DrawMap();
			while (1)
			{
				//The followings are the operations of the map.
				if (_kbhit())
				{
					MapSystem Map;
					SetPosition(Map.GetMapCursorPositionX(), Map.GetMapCursorPositionY());
					cout << " " << endl;
					SetPosition(62, 10);
					cout << "  " << flush;

					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.MapClear();
						Scene.RedrawCharaters();
						break;//If 'k' is pressed, the player will exit the map.
					}
					switch (tolower(hitkey))
					{
					case MOVE_UP:
					{

						SetPosition(Map.GetMapCursorPositionX(), Map.GetMapCursorPositionY()); } break;
					case MOVE_DOWN:
					{
						SetPosition(Map.GetMapCursorPositionX(), Map.GetMapCursorPositionY()); } break;
					case MOVE_LEFT:
					{
						SetPosition(Map.GetMapCursorPositionX(), Map.GetMapCursorPositionY()); }break;
					case MOVE_RIGHT:
					{
						SetPosition(Map.GetMapCursorPositionX(), Map.GetMapCursorPositionY()); } break;
					default:
						SetPosition(Map.GetMapCursorPositionX(), Map.GetMapCursorPositionY());
						break;
					}
					cout << "->" << flush;
				}
			}
		}; break;
		case 10: {		
				Scene.DrawAccomplishmentsArea();
				while (1)
				{
					if (_kbhit())
					{
						hitkey = _getch();
						if (hitkey == 'k')
						{
							Scene.AreasClear();
							Scene.RedrawCharaters();
							break;
						}
					}
				}
		}break;
		case 12: {
			Scene.DrawSelectSavedDataArea();
			SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
			cout << "->" << flush;
			//The followings are the operations of reading the saved data.
			while (1)
			{
				if (_kbhit())
				{
					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.SelectSavedDataAreaClear();
						Scene.RedrawCharaters();
						break;
					}

					switch (hitkey)
					{
					case MENU_UP: {
						if (Scene.GetSavedDataCursorPositionY() >= 12)
						{
							SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
							cout << "  " << flush;
							Scene.SetSavedDataCursorPositionY(Scene.GetSavedDataCursorPositionY() - 1);
						}
					}break;
					case MENU_DOWN: {
						if (Scene.GetSavedDataCursorPositionY() <= 19)
						{
							SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
							cout << "  " << flush;
							Scene.SetSavedDataCursorPositionY(Scene.GetSavedDataCursorPositionY() + 1);
						}
					}break;
					case MENU_PRESS: {
						//The class FileIO will start to work here.
						switch (Scene.GetSavedDataCursorPositionY())//The cursor's y position will decide which data to be changed.
						{
						case 11: {			
							fileIO.ReadSavedData("saveddata1.txt"); //Then the important information in the game will be initialized.
						}break;
						case 12: {
							fileIO.ReadSavedData("saveddata2.txt");
						}break;
						case 13: {
							fileIO.ReadSavedData("saveddata3.txt");
						}break;
						case 14: {
							fileIO.ReadSavedData("saveddata4.txt");
						}break;
						case 15: {
							fileIO.ReadSavedData("saveddata5.txt");
						}break;
						case 16: {
							fileIO.ReadSavedData("saveddata6.txt");
						}break;
						case 17: {
							fileIO.ReadSavedData("saveddata7.txt");
						}break;
						case 18: {
							fileIO.ReadSavedData("saveddata8.txt");
						}break;
						case 19: {
							fileIO.ReadSavedData("saveddata9.txt");
						}break;
						case 20: {
							fileIO.ReadSavedData("saveddata10.txt");
						}break;
						}
					}break;
					}
					SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
					cout << "->" << flush;
				}
			}
		}; break;
		case 14: {
			Scene.DrawSelectSavedDataArea();
			SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
			cout << "->" << flush;
			while (1)
			{
				if (_kbhit())
				{
					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.SelectSavedDataAreaClear();
						Scene.RedrawCharaters();
						break;
					}

					switch (tolower(hitkey))
					{
					case MENU_UP: {
						if (Scene.GetSavedDataCursorPositionY() >=12)
						{
							SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
							cout << "  " << flush;
							Scene.SetSavedDataCursorPositionY(Scene.GetSavedDataCursorPositionY() - 1);
						}
					}break;
					case MENU_DOWN: {
						if (Scene.GetSavedDataCursorPositionY() <= 19)
						{
							SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
							cout << "  " << flush;
							Scene.SetSavedDataCursorPositionY(Scene.GetSavedDataCursorPositionY() + 1);
						}
					}break;
					}
					SetPosition(Scene.GetSavedDataCursorPositionX(), Scene.GetSavedDataCursorPositionY());
					cout << "->" << flush;
				}
			}
		}; break;
		default:;
			break;
		}
	}; break;
	}
	SetPosition(Scene.GetMenuPositionX(), Scene.GetMenuPositionY());
	cout << "->" << flush;

}

void GameController::BattlingCursorMoving()
{
	//The function used to make the cursor in the battle move by w,a,s,d.
	string cursorImage = Battle.GetCursorImage();

	SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
	cout << " " << endl;
	SetPosition(62, 10);
	cout << "  " << flush;

	switch (tolower(hitkey))
	{
	case MOVE_UP:
	{
		Battle.SetCursorPositionY(Battle.GetCursorPositionY() - 1);
		SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
	}; break;
	case MOVE_DOWN:
	{
		Battle.SetCursorPositionY(Battle.GetCursorPositionY() + 1);
		SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
	} break;
	case MOVE_LEFT:
	{
		Battle.SetCursorPositionX(Battle.GetCursorPositionX() - 1);
		SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
	}break;
	case MOVE_RIGHT:
	{
		Battle.SetCursorPositionX(Battle.GetCursorPositionX() + 1);
		SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());

	} break;
	default:
		SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
		break;
	}
	cout << cursorImage << flush;
	Scene.RedrawCharaters();
}

void GameController::UsingBattlingMenu()
{
	SetPosition(62, 20);
	cout << "  " << flush;
	bool if_end = false;
	switch (tolower(hitkey))
	{
	case BATTLING_MENU_APPEAR: {
		if (Battle.GetCursorPositionX() == GameHero.GetPositionX() && Battle.GetCursorPositionY() == GameHero.GetPositionY())
		//If the cursor's position is the same as the hero's position
		{
			//The followings will show the information of the hero.
			Battle.SetBattleMenuCursorPositionX(22);
			Battle.SetBattleMenuCursorPositionY(10);
			Scene.DrawBattleMenuOfHero();
			SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
			cout << "->" << flush;

			while (1)
			{
				if (if_end)
				{
					Scene.BattleAreasClear();
					Scene.RedrawCharaters();
					break;//Exit the menu.
				}
				if (_kbhit())
				{
					hitkey = _getch();
					if (hitkey == 'k')
					{
						Scene.BattleAreasClear();
						Scene.RedrawCharaters();
						if_end = true;
						break;
					}
					//The operation of the menu of hero.
					else
					{
						switch (tolower(hitkey))
						{

						case BATTLING_MENU_UP: {
							SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
							cout << "  " << flush;
							if (Battle.GetBattleMenuCursorPositionY() >= 12)
								Battle.SetBattleMenuCursorPositionY(Battle.GetBattleMenuCursorPositionY() - 2);
						}break;
						case BATTLING_MENU_DOWN: {
							SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
							cout << "  " << flush;
							if (Battle.GetBattleMenuCursorPositionY() <= 14)
								Battle.SetBattleMenuCursorPositionY(Battle.GetBattleMenuCursorPositionY() + 2);
						}break;
						case BATTLING_MENU_PRESS:
						{
							//The menu's cursor's position decides what to do next.
							switch (Battle.GetBattleMenuCursorPositionY())
							{
							case 10: {
								Scene.BattleAreasClear();
								Battle.ShowHeroMoveArea(GameHero.GetAbility("movespeed"), { GameHero.GetPositionX(),GameHero.GetPositionY() });
								//Move the hero.
								while (1)
								{
									Battle.CursorFlashing();
									if (if_end)
									{
										break;
									}
									if (_kbhit())
									{
										hitkey = _getch();
										if (tolower(hitkey) == 'k')
										{
											if_end = true;
											break;
										}
										else 
										{
											bool if_move = false;
											if_hero_can_move = false;
											if_move = Battle.IfHeroCanMove(GameHero.GetAbility("movespeed")+1, { GameHero.GetPositionX(),GameHero.GetPositionY() });
											//This function will decide if the hero is inside the range of moving.

											switch (tolower(hitkey))
											{
											case MOVE_UP:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionY(Battle.GetCursorPositionY() - 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												cout << Battle.GetCursorImage() << flush;
											}break;
											case MOVE_DOWN:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionY(Battle.GetCursorPositionY() + 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY()); 
												cout << Battle.GetCursorImage() << flush;;
											}break;
											case MOVE_LEFT:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionX(Battle.GetCursorPositionX() - 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												cout << Battle.GetCursorImage() << flush;
											}break;
											case MOVE_RIGHT:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionX(Battle.GetCursorPositionX() + 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY()); 
												cout << Battle.GetCursorImage() << flush;
											}break;
											case BATTLING_MENU_PRESS:
											{
												if (if_move)
												{
													//The tip:Sure to end moving?
													Scene.DrawBattleEndMovingWarming();

													while (1)
													{
														if (_kbhit())
														{
															hitkey = _getch();

															if (tolower(hitkey) == 'j')
															{
																Battle.HeroMoveAreaClear();
																Scene.RedrawCharaters();
															}
															else if (tolower(hitkey) == 'k')
															{
																if_move = false;
															}

															if (if_move)
															{
																Scene.BattleEndMovingWarmingClear();
																this->SetPosition(GameHero.GetPositionX(), GameHero.GetPositionY());
																cout << " " << flush;
																this->SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
																GameHero.SetPositionX(Battle.GetCursorPositionX());
																GameHero.SetPositionY(Battle.GetCursorPositionY());
																cout << GameHero.GetImage() << flush;
																Scene.RedrawCharaters();
																if_end = true;
																break;
															}
															else
															{
																Scene.BattleEndMovingWarmingClear();
																Battle.HeroMoveAreaClear();
																Scene.RedrawCharaters();
																if_end = true;
																break;
															}
														}
													}//end while
												}//end if
											}; break;
											}//end swicth
										}//end else
										Scene.RedrawCharaters();
									}//end if(_kbhit())
								}//end while
								Battle.HeroMoveAreaClear();
							}; break;
							case 12: {
								//Attack the enemy.
								Scene.BattleAreasClear();
								Battle.ShowHeroAttackArea(GameHero.GetCurrentWeapen().GetRange() , { GameHero.GetPositionX(),GameHero.GetPositionY() });
								//Move the hero.
								while (1)
								{
									Battle.CursorFlashing();
									if (if_end)
									{
										break;
									}
									if (_kbhit())
									{
										hitkey = _getch();
										if (tolower(hitkey) == 'k')
										{
											if_end = true;
											break;
										}
										else
										{
											bool if_attack = false;
											bool if_move = false;
											if_hero_can_move = false;
											if_hero_can_attack = false;
											if_move = Battle.IfHeroCanMove(GameHero.GetCurrentWeapen().GetRange() + 1, { GameHero.GetPositionX(), GameHero.GetPositionY() });
											//IfHeroCanMove is used to draw the area the hero can attack.
											if_attack = Battle.IfHeroCanAttack(GameHero.GetCurrentWeapen().GetRange()+1, { GameHero.GetPositionX(),GameHero.GetPositionY() });
											//This function will decide if the hero is inside the range of moving.

											switch (tolower(hitkey))
											{
											case MOVE_UP:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionY(Battle.GetCursorPositionY() - 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												cout << Battle.GetCursorImage() << flush;
											}break;
											case MOVE_DOWN:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionY(Battle.GetCursorPositionY() + 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												cout << Battle.GetCursorImage() << flush;;
											}break;
											case MOVE_LEFT:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionX(Battle.GetCursorPositionX() - 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												cout << Battle.GetCursorImage() << flush;
											}break;
											case MOVE_RIGHT:
											{
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												if (if_move)
													cout << "¡õ" << flush;
												else
													cout << " " << flush;
												Battle.SetCursorPositionX(Battle.GetCursorPositionX() + 1);
												SetPosition(Battle.GetCursorPositionX(), Battle.GetCursorPositionY());
												cout << Battle.GetCursorImage() << flush;
											}break;
											case BATTLING_MENU_PRESS:
											{
												if (if_attack)
												{
													//The tip:Sure to end attacking?
													Scene.DrawBattleEndAttackingWarming();

													while (1)
													{
														if (_kbhit())
														{
															hitkey = _getch();

															if (tolower(hitkey) == 'j')
															{
																Battle.HeroAttackAreaClear();
																Scene.RedrawCharaters();
															}
															else if (tolower(hitkey) == 'k')
															{
																if_attack = false;
															}

															if (if_attack)
															{
																Scene.BattleEndAttackingWarmingClear();
																Battle.SetHeroAttackEnemy();
																Battle.SetCurrentAttackType( GameHero.GetCurrentWeapen().GetKind());//Phycis or magic.
																Scene.RedrawCharaters();
																if_end = true;
																break;
															}
															else
															{
																Scene.BattleEndAttackingWarmingClear();
																Battle.HeroAttackAreaClear();
																Scene.RedrawCharaters();
																if_end = true;
																break;
															}
														}
													}//end while
												}//end if
											}; break;
											}//end swicth
										}//end else
										Scene.RedrawCharaters();
									}//end if(_kbhit())
								}//end while
								Battle.HeroAttackAreaClear();
							}; break;
							case 14: {
								//Get the information of the hero.

							}; break;
							case 16: {
								//Exit the menu and go back to the game.
								Scene.BattleAreasClear();
								Scene.RedrawCharaters();
								if_end = true;
							}; break;
							default:break;
							}

						}; break;
						default: break;
						}
					}

					if (!if_end)
					{
						SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
						cout << "->" << flush;
					}
				}
			}
		}
		else
		{
			int i = 0;
			bool IsBlank = true;

			for (i = 0; i != Battle.GetEnemyAmount(); ++i)
			{
				//To find whether any enemy's current position fits the cursor's position.
				if (Battle.GetCursorPositionX() == Battle.GetEnemyAtIndex(i).GetPositionX() && Battle.GetCursorPositionY() == Battle.GetEnemyAtIndex(i).GetPositionY())
				{
					SetPosition(22, 10);
					cout << "->" << flush;
					//The followings will show the information of the enemy.
					Scene.DrawBattleMenuOfEnemy();
					while (1)
					{
						if (_kbhit())
						{
							hitkey = _getch();
							if (hitkey == 'k')
							{
								Scene.BattleAreasClear();
								Scene.RedrawCharaters();
								break;
							}
							else if (hitkey == 'j')
							{
								//Show the information of the enemy.
							}
						}
					}

					IsBlank = false;
					break;//Ignore the rest of the Enemy in the vector.
				}
			}
			//If the cursor's position is the same as the blank
			if (IsBlank)
			{
				//The followings will show the information of some other operations.
				Battle.SetBattleMenuCursorPositionX(22);
				Battle.SetBattleMenuCursorPositionY(9);
				Scene.DrawBattleMenuOfBlank();
				SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
				cout << "->" << flush;
				bool if_end = false;
				while (1)
				{
					if (if_end)
					{
						Scene.BattleAreasClear();
						Scene.RedrawCharaters();
						break;//Exit the menu.
					}
					if (_kbhit())
					{
						
						hitkey = _getch();
						if (hitkey == 'k')
						{
							Scene.BattleAreasClear();
							Scene.RedrawCharaters();
							break;//Exit the menu.
						}

						switch (tolower(hitkey))
						{
						case BATTLING_MENU_UP: {
							SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
							cout << "  " << flush;
							if (Battle.GetBattleMenuCursorPositionY() >= 11)
								Battle.SetBattleMenuCursorPositionY(Battle.GetBattleMenuCursorPositionY() - 2);
						}break;
						case BATTLING_MENU_DOWN: {
							SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
							cout << "  " << flush;
							if (Battle.GetBattleMenuCursorPositionY() <= 15)
								Battle.SetBattleMenuCursorPositionY(Battle.GetBattleMenuCursorPositionY() + 2);
						}break;
						case BATTLING_MENU_PRESS: {
							//The menu's cursor's position decides what to do next.
							switch (Battle.GetBattleMenuCursorPositionY())
							{
							case 9: {
								//End the player's operation of this round and let the computer begin to controll the enemies.
							}; break;
							case 11: {
								//Show the information of the player's troop.
							}; break;
							case 13: {
								//Show the information of the enemy's troop.
							}; break;
							case 15: {
								//Show the condition of victory and failure.
								Scene.BattleAreasClear();
								Scene.DrawBattlePurpose("²âÊÔ", "²âÊÔ");
								while (1)
								{
									if (tolower(_getch()) == 'k')
									{
										Scene.BattlePurposeClear();
										Scene.RedrawCharaters();
										if_end = true;
										break;
									}
								}
							}; break;
							case 17: {
								//Go back to the game.
								Scene.BattleAreasClear();
								Scene.RedrawCharaters();
								if_end = true;
							}; break;
							default:break;
							}
						}break;
						default:break;
						}
						if (!if_end)
						{
							SetPosition(Battle.GetBattleMenuCursorPositionX(), Battle.GetBattleMenuCursorPositionY());
							cout << "->" << flush;
						}
					}
				}
			}
		}
	}
	}
}