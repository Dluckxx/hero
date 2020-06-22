#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include "Unit.h"
#include "Battlefield.h"

using namespace std;

#define ROW 10
#define COL 20

int main() {
    START:
    char input;
    Battlefield battlefield(ROW, COL);
    Unit hero(0, 0, 'h', "hero");
    Unit enemy(0, 0, 'e', "enemy");
    Unit tower_friend(ROW - 1, 0, 'F', "tower_friend");
    Unit tower_enemy(0, COL - 1, 'E', "tower_enemy");

    //init
    random_device rd;
    uniform_int_distribution<> distRow(1, ROW - 1);
    uniform_int_distribution<> distCol(1, COL - 1);
    //random location of two player(one bot)
    hero.setCol(distCol(rd));
    hero.setRow(distRow(rd));
    enemy.setCol(distCol(rd));
    enemy.setRow(distRow(rd));
    //add unit to battlefield
    battlefield.addUnit(&hero);
    battlefield.addUnit(&enemy);
    battlefield.addUnit(&tower_friend);
    battlefield.addUnit(&tower_enemy);
    //load the save
    cout << "do you want read your save?(y or n):" << ends;
    cin >> input;
    if (input == 'y') {
        ifstream readSave("save.txt");
        int a, b, c, d;
        readSave >> a >> b >> c >> d;
        hero.setRow(a);
        hero.setCol(b);
        enemy.setRow(c);
        enemy.setCol(d);
        cout << "read success!" << endl << "game will be run after 3s!" << endl;
        sleep(3);
    }
    //first show the map
    battlefield.updateMap();
    battlefield.print(cout);

    //change position of enemy
    Unit *enemy_ptr = &enemy;
    Unit *tower_friend_ptr = &tower_friend;
    Battlefield *battlefield_ptr = &battlefield;
    thread t([=] {
        clock_t flag = clock();
        while (!enemy_ptr->compare(*tower_friend_ptr)) {
            if (clock() - flag > 1000000) {
                flag = clock();
                int row = 0, col = 0;
                if (enemy_ptr->getRow() == tower_friend_ptr->getRow()) row = 0;
                else if (enemy_ptr->getRow() > tower_friend_ptr->getRow()) row = -1;
                else if (enemy_ptr->getRow() < tower_friend_ptr->getRow()) row = 1;
                if (enemy_ptr->getCol() == tower_friend_ptr->getCol()) col = 0;
                else if (enemy_ptr->getCol() > tower_friend_ptr->getCol()) col = -1;
                else if (enemy_ptr->getCol() < tower_friend_ptr->getCol()) col = 1;
                if (abs(row) && !abs(col)) enemy_ptr->setRow(enemy_ptr->getRow() + row);
                else if (!abs(row) && abs(col)) enemy_ptr->setCol(enemy_ptr->getCol() + col);
                else if (abs(row) && abs(col)) {
                    random_device rd;
                    bernoulli_distribution dist;
                    dist(rd) ? col = 0 : row = 0;
                    battlefield_ptr->moveUnit(enemy_ptr, row, col);
                }
                battlefield_ptr->updateMap();
                battlefield_ptr->print(cout);
            }
        }
        cout << "you lose! because enemy has destroy your tower!" << endl;
        exit(0);
    });
    t.detach();

    system("stty -icanon");
    ofstream file("save.txt");
    while (cin >> input) {
        //input
        switch (input) {
            case 'd':
                battlefield.moveUnit(&hero, 0, 1);
                break;
            case 'a':
                battlefield.moveUnit(&hero, 0, -1);
                break;
            case 's':
                battlefield.moveUnit(&hero, 1, 0);
                break;
            case 'w':
                battlefield.moveUnit(&hero, -1, 0);
                break;
            case 'n':
                goto START;
            case 'q':
                file << hero.getRow() << " " << hero.getCol() << endl;
                file << enemy.getRow() << " " << enemy.getCol() << endl;
                file.flush();
                file.close();
                cout << endl << "saved!" << endl;
                return 0;
            default:
                break;
        }
        //output game
        battlefield.updateMap();
        battlefield.print(cout);

        if (hero.compare(tower_enemy)) {
            cout << "you win!" << endl;
            break;
        } else if (hero.compare(enemy)) {
            cout << "you were killed by enemy" << endl;
            break;
        }
    }
    return 0;
}