#include "Dem.hpp" 
	
Dem::Dem(string gameName)
{
    _gameName = gameName;
    startRoomID = -1;
};

int Dem::indexOf(char el) {
    int index;
    for (int i = 0; i < 4; i++) {
        if (dirs[i] == el) {
            index = i;
        }
    }
    return index;
};

void Dem::createRoom(string roomChar, string arr[][24]) {
    roomIDs.push_back(roomChar);
    for (int i = 0; i < 24; i++) {
        for (int e = 0; e < 24; e++) {
            rooms[roomIDs.size()-1][i][e] = arr[i][e];
        }
    }
};

void Dem::createChar(string charChar, string charName, string charAge, string charGenter) {
    charIDs.push_back(charChar);
    cout << charChar << ' ' << charName << ' ' << charAge << ' ' << charGenter << endl;
    chars[charIDs.size()-1][0] = charName;
    chars[charIDs.size()-1][1] = charAge;
    chars[charIDs.size()-1][2] = charGenter;
};

void Dem::startRoom(string name) {
        for (int i = 0; i < roomIDs.size(); i++) {
            if (roomIDs[i] == name) {
                startRoomID = i;
                roomID = i;
                break;
            }
        }
        if (startRoomID == -1) {
            cout << "Ender an existing room! \n";
        } else {
            for (int i = 0; i < 24; i++) {
                for (int e = 0; e < 24; e++) {
                    curentRoom[i][e] = rooms[startRoomID][i][e];
                }
            };
        }
};

void Dem::createItem(string itemName, string itemDescription) {
    itemIDs.push_back(itemName);
    items[itemIDs.size()-1] = itemDescription;
};

void Dem::createObject(string objChar, string type, string objName, string to) {
    objIDs.push_back(objChar);
    objs[objIDs.size()-1][0] = objName;
    objs[objIDs.size()-1][1] = type;
    objs[objIDs.size()-1][2] = to;
};

void Dem::switchRoom(string roomChar) {
    for (int i = 0; i < roomIDs.size(); i++) {
        if (roomIDs[i] == roomChar) {
            for (int e = 0; e < 24; e++) {
                for (int x = 0; x < 24; x++) {
                    rooms[roomID][e][x] = curentRoom[e][x];
                }
            }
            roomID = i;
            for (int e = 0; e < 24; e++) {
                for (int x = 0; x < 24; x++) {
                    curentRoom[e][x] = rooms[i][e][x];
                }
            }
        }
    }
};

int* Dem::getPos() {
    return posxy;
}

void Dem::place(int x, int y, string rep) {
    curentRoom[x-1][y-1] = rep;
};

string* Dem::getObj(string objChar) {
    for (int i = 0; i < objIDs.size(); i++) {
        if (objChar == objIDs[i]){
            return objs[i];
        }
    }
    return objs[0]; 
};

string* Dem::getChar(string charChar) {
    for ( int i = 0; i < charIDs.size(); i++) {
        if (charChar == charIDs[i]) {
            return chars[i];
        }
    }
    return chars[0];
};

string Dem::loc(int x, int y) {
    string a;
    x = x - 1;
    y = y - 1;
    if ((x < 24) || (y < 24)) {
        return curentRoom[x][y];
    } else {
        return "Out of map";
    }
    return " ";
};

string* Dem::getInv() {
    return inventar;
};

void Dem::turn(string dir) {
    if (dir == "left") {
        int tr = indexOf(oren)-1;
        if (tr < 0) {
            oren = dirs[3];
        } else if (tr > 3) {
            oren = dirs[0];
        } else {
            oren = dirs[tr];
        }
    }
    else if (dir == "right") {
        int tr = indexOf(oren)+1;
        if (tr < 0) {
            oren = dirs[3];
        } else if (tr > 3) {
            oren = dirs[0];
        } else {
            oren = dirs[tr];
        }
    }
    else {
        cout << "Command is not known\n";
    }
};

char Dem::orent() {
    return oren;
};

void Dem::move(string dir) {
    if (dir == "forward") {
        if ((oren == 'N') || (oren == 'S')){
            posxy[0] = posxy[0] + dirIDs[indexOf(oren)];
        }
        if ((oren == 'W') || (oren == 'E')){
            posxy[1] = posxy[1] + dirIDs[indexOf(oren)];
        }
    }
    if (dir == "backwards") {
        if ((oren == 'N') || (oren == 'S')){
            posxy[0] = posxy[0] - dirIDs[indexOf(oren)];
        }
        if ((oren == 'W') || (oren == 'E')){
            posxy[1] = posxy[1] - dirIDs[indexOf(oren)];
        }
    }
    if (dir == "left") {
        if ((oren == 'N') || (oren == 'S')){
            posxy[1] = posxy[1] + dirIDs[indexOf(oren)];
        }
        if ((oren == 'W') || (oren == 'E')){
            posxy[0] = posxy[0] - dirIDs[indexOf(oren)];
        }
    }
    if (dir == "right") {
        if ((oren == 'N') || (oren == 'S')){
            posxy[1] = posxy[1] - dirIDs[indexOf(oren)];
        }
        if ((oren == 'W') || (oren == 'E')){
            posxy[1] = posxy[1] + dirIDs[indexOf(oren)];
        }
    }
};
