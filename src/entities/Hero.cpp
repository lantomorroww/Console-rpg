#include "entities/Hero.h"
#include "actions/Action.h"
#include <iostream>

Hero::Hero(int hpMax, int manaMax, const std::string& heroName, int armorMax, int startX, int startY)
    : hp(hpMax), mana(manaMax), maxMana(manaMax), name(heroName), armor(armorMax), x(startX), y(startY) {}
void Hero::move(char direction) {
    switch (direction) {
        case 'w': y--; break;
        case 's': y++; break;
        case 'a': x--; break;
        case 'd': x++; break;
    }
}

void Hero::draw(std::vector<std::vector<char>>& map) const {

    map[y][x] = 'P';
}

void Hero::show() const {
    std::cout << "Name: " << name << "\nHP: " << hp << "\nMana: " << mana << "\nArmor: " << armor << "\n";
}

void Hero::takeDamage(int damage) {
    if (isDefending) {
        damage /= 2;
        isDefending = false; // сбрасываем после применения
    }
    hp -= damage;
    if (hp < 0) hp = 0;
}

std::unique_ptr<Action> Hero::getAction(int choice) const {
    switch (choice) {
        case 1: return std::make_unique<AttackAction>();
        case 2: return std::make_unique<DefendAction>();
        case 3: return std::make_unique<SpecialAction>();
        default: return nullptr;
    }
}
