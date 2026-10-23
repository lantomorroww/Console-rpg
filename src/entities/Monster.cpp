#include "entities/Monster.h"
#include <iostream>

Monster::Monster(int hpMax, int manaMax, const std::string& monName, int armorMax, int startX, int startY)
    : hp(hpMax), mana(manaMax), name(monName), armor(armorMax), x(startX), y(startY) {}

void Monster::show() const {
    std::cout << "Monster: " << name << ", HP: " << hp << ", Mana: " << mana << ", Armor: " << armor << "\n";
}