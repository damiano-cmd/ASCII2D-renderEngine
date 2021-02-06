#include "Elements.hpp"

room::room() {};
room::room(char** roo, int w, int h) {
	_rm = new char*[h];
	_w = w;
	_h = h;
	for (int i = 0; i < h; i++) {
		_rm[i] = new char[w];
		for (int e = 0; e < w; e++) {
			_rm[i][e] = roo[i][e];
		}
	}
};
char** room::getFT(int xf, int yf, int xt, int yt ){
	char** ret = new char*[yt-yf];
	for (int i = yf; i < yt; i++) {
		ret[i-yf] = new char[xt-xf];
		for (int e = xf; e < xt; e++) {
			ret[i-yf][e-xf] = _rm[i][e];
		}
	}
	return ret;
};
char room::getAt(int x, int y) {
	return _rm[y][x];
};
void room::edit(int x, int y, char rep) {
	_rm[y][x] = rep;
};
int* room::size() {
    int* ret = new int[2]{_w, _h};
    return ret;
};
int** room::findAll(char ch) {
	int** indexs = new int*[3];
	vector<int> x;
	vector<int> y;
	for (int i = 0; i < _h; i++) {
		for (int e = 0; e < _w; e++) {
			if (_rm[i][e] == ch) {
				x.push_back(e);
				y.push_back(i);
			}
		}
	}
	int xs = x.size();
	int ys = y.size();
	indexs[0] = new int[1]{xs};
	indexs[1] = new int[xs];
	indexs[2] = new int[ys];
	for (int i = 0; i < x.size(); i++) {
		indexs[1][i] = x[i];
		indexs[2][i] = y[i];
	}
	return indexs;
};
int* room::find(char ch) {
	int* ret = new int[2]{0, 0};
	for (int i = 0; i < _h; i++) {
		for (int e = 0; e < _w; e++) {
			if (_rm[i][e] == ch) {
				ret[0] = e;
				ret[1] = i;
				return ret;
			}
		}
	}
	return ret;
};

sprite::sprite() {};
sprite::sprite(char** sprite, int w, int h) {
	_sprite = new char*[h];
	width = w;
	height = h;
	for (int i = 0; i < h; i++) {
		_sprite[i] = new char[w];
		for (int e = 0; e < w; e++) {
			_sprite[i][e] = sprite[i][e];
		}
	}
};
char** sprite::get() {
    return _sprite;
};
int* sprite::size() {
    int* ret = new int[2]{width, height};
    return ret;
};

object::object() {};
object::object(sprite spr, string name, int x, int y) {
    _spr = spr;
	_name = name;
};
void object::move(int x, int y) {
    _x = x;
    _y = y;
};
int* object::size() {
    return _spr.size();
};
int* object::pos() {
    int* ret = new int[2]{_x, _y};
    return ret;
};
string object::name() {
	return _name;
};
sprite object::getSpr() {
    return _spr;
};

display::display() {};
display::display(int width, int height){
	_width = width;
	_height = height;
};
void display::run(char** arr, int x, int y) {
	cout << endl;
	system("CLS");
	for (int i = y; i < _height; i++) {
		for (int e = x; e < _width; e++) {
			cout << arr[i][e];
		}
		cout << endl;
	}
};
char** display::draw(object obj, char** rom, int* size) {
	char** ret = rom;
	sprite sprc = obj.getSpr();
	char** spr = sprc.get();
	int* os = sprc.size();
	int* pos = obj.pos();
	for (int i = pos[1]; i < pos[1]+os[1]; i++) {
		for (int e = pos[0]; e < pos[0]+os[0]; e++) {
			if (spr[i-pos[1]][e-pos[0]] != ' ') {
				ret[i][e] = spr[i-pos[1]][e-pos[0]];
			}
		}
	}
    return ret;
};

colision::colision() {};
bool colision::byTwo(object obj1, object obj2) {
	int* obj1p = obj1.pos();
	int* obj1s = obj1.size();
	int* obj2p = obj2.pos();
	int* obj2s = obj2.size();
	if (
		(
			(obj1p[0] <= obj2p[0]) && (obj2p[0] <= (obj1p[0]+obj1s[0]-1)) ||
			(obj1p[0] <= (obj2p[0]+obj2s[0]-1)) && ((obj2p[0]+obj2s[0]-1) <= (obj1p[0]+obj1s[0]-1))
		) && (
			(obj1p[1] <= obj2p[1]) && (obj2p[1] <= (obj1p[1]+obj1s[1]-1)) ||
			(obj1p[1] <= (obj2p[1]+obj2s[1]-1)) && ((obj2p[1]+obj2s[1]-1) <= (obj1p[1]+obj1s[1]-1))
		) 
		){
			return true;
		}
	return false;
};
int** colision::byVector(vector<object> objs) {
	int** ret = new int*[objs.size()+1];
	ret[0] = new int[2];
	ret[0][0] = 1;
	for (int i = 0; i < objs.size(); i++) {
		for (int e = i+1; e < objs.size(); e++) {
			bool col = byTwo(objs[i], objs[e]);
			if (col == true) {
				ret[ret[0][0]] = new int[2];
				ret[ret[0][0]][0] = i;
				ret[ret[0][0]][1] = e;
				ret[0][0]++;
			}
		}
	}
	return ret;
};

void move(object &obj, char key, room rom, char col) {
    int* pos = obj.pos();
    int* siz = obj.size();
    switch (key) {
        case 'w':
            if (rom.getAt(pos[0], pos[1]-1) != col) {
                obj.move(pos[0], pos[1]-1);
            }
            break;
        case 's':
            if (rom.getAt(pos[0], pos[1]+siz[1]) != col) {
                obj.move(pos[0], pos[1]+1);
            }
            break;
        case 'a':
            if (rom.getAt(pos[0]-1, pos[1]) != col) {
                obj.move(pos[0]-1, pos[1]);
            }
            break;
        case 'd':
            if (rom.getAt(pos[0]+siz[0], pos[1]) != col) {
                obj.move(pos[0]+1, pos[1]);
            }
            break;
    }
};
