//
// Created by 杜铁生 on 2020/6/21.
//

#ifndef HERO_UNIT_H
#define HERO_UNIT_H

#include <string>

class Unit {
public:
    //constructor
    Unit(unsigned int row, unsigned int col, char skin, std::string name);

    /**
     * compare the position
     * @param unit
     * @return bool result
     */
    bool compare(const Unit& unit) const;

    unsigned int getRow() const;

    void setRow(unsigned int i);

    unsigned int getCol() const;

    void setCol(unsigned int i);

    char getSkin() const;

    void setSkin(char unitSkin);

    const std::string &getName() const;

    void setName(const std::string &unitName);

private:
    unsigned int row;
    unsigned int col;
    char skin;
    std::string name;
};


#endif //HERO_UNIT_H
