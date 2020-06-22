//
// Created by 杜铁生 on 2020/6/21.
//

#include "Battlefield.h"

Battlefield::Battlefield(unsigned int row, unsigned int col) : ROW(row), COL(col) {
    map.resize(row, std::vector<char>(col, ' '));
}

std::ostream &Battlefield::print(std::ostream &out) {
    out << std::endl << std::string(map.front().size() + 2, '#') << std::endl;
    for (const auto &row : map) {
        out << '#';
        for (const auto &item : row) {
            out << item;
        }
        out << '#' << std::endl;
    }
    out << std::string(map.front().size() + 2, '#') << std::endl;
    return out;
}

void Battlefield::addUnit(Unit *unit) {
    this->units.push_back(unit);
}

bool Battlefield::removeUnit(const std::string &name) {
    for (auto iter = units.begin(); iter != units.end(); ++iter) {
        if ((*iter)->getName() == name) {
            units.erase(iter);
            return true;
        }
    }
    return false;
}

void Battlefield::updateMap() {
    //clear all map location
    for (auto &row : map) {
        for (auto &col : row) {
            col = ' ';
        }
    }
    //add all units
    for (const auto &unit : units) {
        map[unit->getRow()][unit->getCol()] = unit->getSkin();
    }
}

void Battlefield::moveUnit(Unit *unit, int rowOffset, int colOffset) const {
    if (unit->getRow() + rowOffset > ROW - 1) return;
    if (unit->getRow() + rowOffset < 0) return;
    if (unit->getCol() + colOffset > COL - 1) return;
    if (unit->getCol() + colOffset < 0) return;
    unit->setRow(unit->getRow() + rowOffset);
    unit->setCol(unit->getCol() + colOffset);
}

