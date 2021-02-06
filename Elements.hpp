#ifndef ASCII2D_H
#define ASCII2D_H
#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class room {
		private:
		int _w;
		int _h;
		char** _rm;
		public:
			room();
			room(char** roo, int w=0, int h=0);
			char** getFT(int xf, int yf, int xt, int yt );
			char getAt(int x, int y);
			void edit(int x, int y, char rep);
			int* size();
};

class sprite {
		private:
		int width;
		int height;
		char** _sprite;
		public:
			sprite();
			sprite(char** sprite, int w, int h);
			char** get();
			int* size();
};

class object {
	private:
	string _name;
	sprite _spr;
	int _x;
	int _y;
	public:
		object();
		object(sprite spr, string name, int x=0, int y=0);
		string name();
		int* pos();
		void move(int x, int y);
		int* size();
		sprite getSpr();
};

class display {
		private:
		int _width;
		int _height;
		public:	
			display();
			display(int width, int height);
			void run(char** arr, int x=0, int y=0);
			char** draw(object obj, char** rom, int* size);
};

class colision {
	private:
	public:
		colision();
		bool byTwo(object obj1, object obj2);
		int** byVector(vector<object> objs);
};

void move(object &obj, char key, room rom, char col='#');

#endif