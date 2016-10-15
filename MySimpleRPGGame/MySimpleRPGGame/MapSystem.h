#ifndef __MAP_SYSTEM_H__
#define __MAP_SYSTEM_H__

#include<iostream>
#include<Windows.h>
#include<cstdlib>
#include<vector>
#include<utility>
#include<string>

using namespace std;

class MapSystem {

private:
	vector<MapSystem>places = {};
	int PositionX;
	int PositionY;
	string name;
	pair<int, int>map_cursor_position = {};

public:
	MapSystem();

	int GetPlacePositionXAtIndex(int index) { return places[index].PositionX; }
	int GetPlacePositionYAtIndex(int index) { return places[index].PositionY; }

	int GetPlacesLength() { return places.size(); }

	int GetMapCursorPositionX() { return map_cursor_position.first; }
	int GetMapCursorPositionY() { return map_cursor_position.second; }

	int SetMapCursorPositionX(int x) { map_cursor_position.first = x; }
	int SetMapCursorPositionY(int y) { map_cursor_position.second = y; }
};

#endif