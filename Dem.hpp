#ifndef DEM_H
#define DEM_H
#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
	
class Dem  
{
	private:
		int indexOf(char el);
		int roomID;
		int startRoomID;
		char oren = 'N';
		char dirs[4] = {'N', 'E', 'S', 'W'};
		int dirIDs [4] = {-1, 1, 1, -1};
		string _name;
		string curentRoom[24][24];
		string _gameName;
		int posxy[2] = {0, 0};
		string inventar[20];

		//world data
		vector<string> roomIDs;
		string rooms[100][24][24];
		vector<string> charIDs;
		string chars[400][3];
		vector<string> itemIDs;
		string items[1500];
		vector<string> objIDs;
		string objs[1000][3];

	public:

		//game initialization
		Dem(string gameName);
		void createRoom(string roomChar, string arr[][24]);
		void createChar(string charChar, string charName, string charAge, string charGenter);
		void createItem(string itemName, string itemDescription);
		void createObject(string objChar, string type, string objName, string to);

		//actions
		void startRoom(string name);
		void switchRoom(string roomChar);
		void move(string dir);
		void turn(string dir);
		char orent();

		//get functions
		int* getPos();
		string * getInv();
		void addToInv(string item);
		string loc(int x, int y);
		void place(int x, int y, string rep);
		string* getObj(string objChar);
		string* getChar(string charChar);
};
#endif