#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "actions/Action.h"

class Hero {
private:
    int hp;
    int mana;
    std::string name;
    int armor;
    int x, y;
    bool isDefending = false;


protected:
    void setHP(int newHp) { hp = newHp; }
    void setMana(int newMana) { mana = newMana; }
    void setArmor(int newArmor) { armor = newArmor; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    int specialDamageBonus = 0;
    int maxMana;

public:
    Hero(int hpMax, int manaMax, const std::string& heroName, int armorMax, int startX, int startY);
    virtual ~Hero() = default;

    // Геттеры
    int getHp() const { return hp; }
    int getMana() const { return mana; }
    int getArmor() const { return armor; }
    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getTotalDamage() const { return getAttackDamage() + specialDamageBonus; }

    // Сеттеры для внешнего управления
    void setStartPosition(int startX, int startY) { x = startX; y = startY; }
    void resetState() { isDefending = false; specialDamageBonus = 0; }

    // Методы движения и отрисовки
    void move(char direction);
    void draw(std::vector<std::vector<char>>& map) const;
    virtual void show() const;
    void addHP(int delta) {
    hp += delta;
    if (hp < 0) hp = 0;
}

    // Виртуальные боевые методы
    virtual int getAttackDamage() const = 0;
    virtual void defend() { isDefending = true; }
    virtual bool useSpecial() { return false; } // по умолчанию неудача
    void takeDamage(int damage); // учитывает защиту

    // Фабрика действий (для боя)
    std::unique_ptr<Action> getAction(int choice) const;
};

#endif
