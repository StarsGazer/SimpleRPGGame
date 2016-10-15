#include"stdafx.h"

#include"FileIO.h"
#include"Character.h"
#include"GameScene.h"
#include"GameController.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

using std::cout;
using std::vector;
using std::cerr;
using std::getline;
using std::endl;
using std::flush;
using std::istringstream;

extern Hero GameHero;

FileIO::FileIO()
{
	this->ReadWeapenData();
	hero_ability_information["Life"] = "";
	hero_ability_information["Attack"] = "";
	hero_ability_information["Defend"] = "";
	hero_ability_information["MagicPower"] = "";
	hero_ability_information["Fortune"] = "";
	hero_ability_information["Level"] = "";
	hero_ability_information["MoveSpeed"] = "";
	hero_ability_information["Technique"] = "";
	hero_ability_information["Agility"] = "";
	hero_ability_information["Money"] = "";
	hero_ability_information["Exp"] = "";
	hero_ability_information["TechniquePoint"] = "";
	hero_ability_information["PositionX"] = "";
	hero_ability_information["PositionY"] = "";
}

bool FileIO::ReadSavedData(string selected_file_name)
{
	fInCharacterData.open(selected_file_name);
	if (fInCharacterData)
	{
		int index = 1;//Related to the word's position of each line.
		bool IsHero = false;
		bool IsTeammate = false;
		bool IsEnemy = false;//Decide which kind of information will be read.
		int enemy_index = 1;//If enemy_index is 1, then a new enemy will be push back into the vector current_enemies.
		int teammate_index = 1;//Similar to the enemy_index.

		while (getline(fInCharacterData, information_words))
		{
			index = 1;
			istringstream is(information_words);
			string information_word = "";
			string current_key = "";
			while (is >> information_word)
			{
				if (index == 1)//Ralated to Hero or Enemy
				{
					if (information_word == "Scene")
					{
						//Decide which scene to be drawn
						IsHero = false;
						IsEnemy = false;
						IsTeammate = false;
					}
					else if (information_word == "Hero")//Then the information of the Hero will be read.
					{
						IsHero = true;
						IsEnemy = false;
						IsTeammate = false;
					}
					else if (information_word == "Enemy")//Then the information of the Enemy will be read.
					{
						if (enemy_index == 1)
						{
							enemy_index++;
							Enemy new_enemy;
							current_enemies.push_back(new_enemy);
						}
						else if (enemy_index != 14)
							enemy_index++;
						else if (enemy_index == 14)
							enemy_index = 1;

						IsHero = false;
						IsEnemy = true;
						IsTeammate = false;
					}
					else if (information_word == "Teammate")//Then the information of the Teammate will be read.
					{
						if (teammate_index == 1)
						{
							teammate_index;
							Teammate new_teammate;
							current_teammates.push_back(new_teammate);
						}
						else if (teammate_index!= 14)
							teammate_index++;
						else if (teammate_index == 14)
							teammate_index = 1;

						IsHero = false;
						IsEnemy = false;
						IsTeammate = true;
					}
				}

				else if (index == 2)
				{
					current_key = information_word;//Related to the kind of the hero,the teammate of the enemy's information.(Except for the scene).
					if (IsHero == false && IsEnemy == false&&IsTeammate==false)//If the information is related to the scene.
						scene_kind = information_word;
				}


				else if (index == 3)
				{
					if (IsHero)
					{
						//If the information can be found in hero_ability_information(such as "Attack")
						if(hero_ability_information.find(current_key)!=hero_ability_information.end())
							hero_ability_information[current_key] = information_word;
						else//These words' kind is string.
						{
						    if (current_key == "Status")
								hero_status = information_word;
							else if (current_key == "Weapens")
								hero_weapens.push_back(information_word);
							else if (current_key == "Accomplishments")
								hero_accomplishments.push_back(information_word);
							else if (current_key == "Techniques")
								hero_techniques.push_back(information_word);
							else if (current_key == "Name")
								hero_name = information_word;
							else if (current_key == "CurrentWeapen")
								hero_current_weapen = information_word;
						}
					}
					else if (IsEnemy)
					{
						int current_enemy_index = current_enemies.size()-1;//Which enemy is being initialized.
						if (hero_ability_information.find(current_key) != hero_ability_information.end())//Use the map the help get the information of the enemies.
						{//The information includes life,attack,defend,magicpower,fortune,level,movespeed,agility.
							current_enemies[current_enemy_index].InitializingAbilities(current_key, atoi(information_word.c_str()));
						}
						else//These words' kind is string.
						{
							if (current_key == "Status")
								current_enemies[current_enemy_index].SetStatus(information_word);
							else if (current_key == "Techniques")
								current_enemies[current_enemy_index].AddTechniques(information_word);
							else if (current_key == "Name")
								current_enemies[current_enemy_index].SetName(information_word);
							else if (current_key == "CurrentWeapen")
								current_enemies[current_enemy_index].GetCurrentWeapen().InitializingWeapen(information_word);
						}
					}
					else if (IsTeammate)
					{
						int current_teammate_index = current_teammates.size() - 1;//Which teammate is being initialized.
						if (hero_ability_information.find(current_key) != hero_ability_information.end())//Use the map the help get the information of the enemies.
						{//The information includes life,attack,defend,magicpower,fortune,level,movespeed,agility.
							current_teammates[current_teammate_index].InitializingAbilities(current_key, atoi(information_word.c_str()));
						}
						else//These words' kind is string.
						{
							if (current_key == "Status")
								current_teammates[current_teammate_index].SetStatus(information_word);
							else if (current_key == "Techniques")
								current_teammates[current_teammate_index].AddTechniques(information_word);
							else if (current_key == "Name")
								current_teammates[current_teammate_index].SetName(information_word);
							else if (current_key == "CurrentWeapen")
								current_teammates[current_teammate_index].GetCurrentWeapen().InitializingWeapen(information_word);
						}
					}
				}
				else if (index > 3)
				{	//These words' kind is string.
					if (IsHero)
					{
						if (current_key == "Weapens")
							hero_weapens.push_back(information_word);
						else if (current_key == "Accomplishments")
							hero_accomplishments.push_back(information_word);
						else if (current_key == "Techniques")
							hero_techniques.push_back(information_word);
					}
					else if (IsEnemy)
					{
						int current_enemy_index = current_enemies.size() - 1;//Which enemy is being initialized.
						if (current_key == "Techniques")
							current_enemies[current_enemy_index].AddTechniques(information_word);
					}
					else if (IsTeammate)
					{
						int current_teammate_index = current_teammates.size() - 1;
						if (current_key == "Techniques")
							current_teammates[current_teammate_index].AddTechniques(information_word);
					}
				}
				index++;
			}
		}

		//Change the information in the game.
		{
			for (auto it = hero_ability_information.begin(); it != hero_ability_information.end();++it)
				GameHero.InitializingAbilities(it->first,atoi((it->second).c_str()));
			//The string read from the file saveddata will be transformed into int.
			GameHero.GetCurrentWeapen().InitializingWeapen(hero_current_weapen);//Initializing the current weapen according to the current weapen's name.
		}

		fInCharacterData.close();
		return true;
	}
	else 
	{
		cout << "Fail to read the saved data" << flush;
		fInCharacterData.close();
		return false;
	}
}

bool FileIO::ReadWeapenData()
{
	fInWeapenData.open("weapendata.txt");

	if (fInWeapenData)
	{
		int index = 1;//To identify which word is read.
		while (getline(fInWeapenData, weapen_data_words))
		{
			istringstream is(weapen_data_words);
			string weapen_data_word;
			string current_name;
			while (is >> weapen_data_word)
			{
				//Then put the data of each weapen into the map weapen_data.
				if (index == 1)
					current_name = weapen_data_word;
				else if (index == 2)
					weapen_data[current_name]["attack"] = atoi(weapen_data_word.c_str());
				else if (index == 3)
					weapen_data[current_name]["hitrate"]= atoi(weapen_data_word.c_str());
				else if (index == 4)
					weapen_data[current_name]["onehit"]= atoi(weapen_data_word.c_str());
				else if (index == 5)
					weapen_data[current_name]["endurance"]= atoi(weapen_data_word.c_str());
				else if (index == 6)
					weapen_data[current_name]["range"] = atoi(weapen_data_word.c_str());
				else if (index == 7)
					weapen_property[current_name] = weapen_data_word;
				else if (index == 8)
					weapen_effect[current_name] = weapen_data_word;
				++index;
			}
		}
		fInWeapenData.close();
		return true;
	}
	else
	{
		fInWeapenData.close();
		return false;
	}

}

int FileIO::GetWeapenData(const string&name,const string&kind)
{
	return weapen_data[name][kind];
}