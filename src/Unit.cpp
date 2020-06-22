//
// Created by 杜铁生 on 2020/6/21.
//
#include <stdexcept>
#include <utility>
#include "Unit.h"


bool Unit::compare(const Unit& unit) const {
    return this->getRow() == unit.getRow() && this->getCol() == unit.getCol();
}

unsigned int Unit::getRow() const {
    return row;
}

void Unit::setRow(unsigned int i) {
    Unit::row = i;
}

unsigned int Unit::getCol() const {
    return col;
}

void Unit::setCol(unsigned int i) {
    Unit::col = i;
}

char Unit::getSkin() const {
    return skin;
}

void Unit::setSkin(char unitSkin) {
    Unit::skin = unitSkin;
}

Unit::Unit(unsigned int row, unsigned int col, char skin, std::string name) : row(row), col(col), skin(skin),
                                                                              name(std::move(name)) {}

const std::string &Unit::getName() const {
    return name;
}

void Unit::setName(const std::string &unitName) {
    Unit::name = unitName;
}
