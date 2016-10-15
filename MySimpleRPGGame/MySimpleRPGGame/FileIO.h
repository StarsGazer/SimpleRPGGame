#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include<utility>
#include"Character.h"

using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::map;
using std::pair;

class FileIO {
public:
	FileIO();

	bool ReadSavedData(string selected_file_name);
	bool ReadWeapenData();
	bool WriteData();
	bool DeleteData();
	string GetWeapenProperty(const string&name){ return weapen_property[name]; }
	string GetWeapenEffect(const string&name) { return weapen_effect[name]; }

	//After the ReadWeapenData is used, this function will be used in the class Weapen's function InitializingWeapen to initialize the current weapen.
	int GetWeapenData(const string&name,const string&kind);
	Enemy& GetEnemyAtIndex(int index) { return current_enemies[index]; }
	size_t GetEnemyAmountOfFile() { return current_enemies.size(); }
	Teammate& GetTeammateAtIndex(int index) { return current_teammates[index]; }
	size_t GetTeammateAmountOfFile() { return current_teammates.size(); }
	bool IfNoEnemy()const { return current_enemies.empty(); }
	bool IfNoTeammate()const { return current_teammates.empty(); }

private:

	vector<string>files_name = {};
	string file_name;
	string selected_file_name;
	ifstream fInWeapenData;
	ifstream fInCharacterData;
	ofstream fOut;
	string information_words;//Words in the file "saveddataX.txt" of each line.
	string weapen_data_words;//Words in the file "weapendata.txt" of each line.
	map<string,string>weapen_property;//The property of each weapen.
	map<string, string>weapen_effect;//The special effect of each weapen.

	//These will be copied from the file, and then will be changed into the data of the game.
	//Used in ReadSaevdData().
	map<string, string>hero_ability_information;
	string hero_status;
	vector<string>hero_weapens;
	string hero_current_weapen;
	string hero_name;
	vector<string>hero_items;
	vector<string>hero_accomplishments;
	vector<string>hero_techniques;
	pair<string,string>hero_position;
	map<string,map<string, int>>weapen_data;
	string scene_kind = "";
	vector<Enemy>current_enemies;
	vector<Teammate>current_teammates;
};

#endif // ! 
