#include <fstream>
#include <conio.h>
#include "Elements.hpp"

int main() {
    char** s = new char*[3];
    s[0] = new char[3]{' ', '|', ' '};
    s[1] = new char[3]{'-', 'o', '-'};
    s[2] = new char[3]{' ', '|', ' '};

    char** r = new char*[10];
    r[0] = new char[15]{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};
    r[1] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[2] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[3] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', ' ', ' ', ' ', '#'};
    r[4] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[5] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[6] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[7] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[8] = new char[15]{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    r[9] = new char[15]{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};

    colision colider;
    room room0(r, 15, 10);
    display dis(15, 10);

    sprite a(s, 3, 3);
    object g(a, "player");
    object h(a, "destoryer");
    int* f = room0.find('.');
    room0.edit(f[0], f[1], ' ');
    g.move(1, 1);
    h.move(f[0], f[1]);
    while (true) {

        char** screen = dis.draw(g, room0.getFT(0,0,room0.size()[0], room0.size()[1]), room0.size());
        screen = dis.draw(h, screen, room0.size());

        dis.run(screen, 0, 0);


        if (colider.byTwo(g, h)) {
            cout << "you crahed\n";
            system("PAUSE");
            return 0;
        }
        
        char input = _getch();
        if (input == 'q') {
            system("PAUSE");
            return 0;
        }
        move(g, input, room0, '#');
    }
    system("PAUSE");
    return 0;
}
