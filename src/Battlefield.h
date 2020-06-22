//
// Created by 杜铁生 on 2020/6/21.
//

#ifndef HERO_BATTLEFIELD_H
#define HERO_BATTLEFIELD_H

#include <vector>
#include <iostream>
#include "Unit.h"

class Battlefield {
public:
    /**
     * generator of Battlefield
     * @param row
     * @param col
     */
    Battlefield(unsigned int row, unsigned int col);

    /**
     * print battlefield to console
     * @param out
     * @return the ostream you give to it
     */
    std::ostream &print(std::ostream &out);

    void addUnit(Unit *unit);

    bool removeUnit(const std::string& name);

    void updateMap();

    void moveUnit(Unit *unit, int rowOffset, int colOffset) const;

private:
    const unsigned int ROW;
    const unsigned int COL;
    std::vector<std::vector<char>> map;
    std::vector<Unit *> units;
};


#endif //HERO_BATTLEFIELD_H
