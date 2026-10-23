#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <memory>
#include <random>

class Monster {
private:
    int hp;
    int mana;
    std::string name;
    int armor;
    int x, y; // координаты в комнате

protected:
    void setHP(int newHp) { hp = newHp; }
    void setMana(int newMana) { mana = newMana; }
    void setArmor(int newArmor) { armor = newArmor; }

public:
    Monster(int hpMax, int manaMax, const std::string& monName, int armorMax, int startX = 0, int startY = 0);
    virtual ~Monster() = default;

    int getHp() const { return hp; }
    int getMana() const { return mana; }
    int getArmor() const { return armor; }
    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int nx, int ny) { x = nx; y = ny; }
    virtual void takeDamage(int damage) { hp -= damage; if (hp < 0) hp = 0; }
    virtual int getAttackDamage() const { return 8; } // база
    virtual void show() const;
};

// Фабричные функции (inline, чтобы избежать множественного определения)
enum class MonsterType { ZOMBIE, GHOST, SKELETON };

struct Zombie : public Monster {
    Zombie(int startX = 0, int startY = 0) : Monster(10, 5, "Zombie", 6, startX, startY) {}
};
struct Ghost : public Monster {
    Ghost(int startX = 0, int startY = 0) : Monster(8, 13, "Ghost", 2, startX, startY) {}
};
struct Skeleton : public Monster {
    Skeleton(int startX = 0, int startY = 0) : Monster(9, 5, "Skeleton", 7, startX, startY) {}
};

inline std::unique_ptr<Monster> createMonster(MonsterType type, int x = 0, int y = 0) {
    switch (type) {
        case MonsterType::ZOMBIE:   return std::make_unique<Zombie>(x, y);
        case MonsterType::GHOST:    return std::make_unique<Ghost>(x, y);
        case MonsterType::SKELETON: return std::make_unique<Skeleton>(x, y);
        default: return nullptr;
    }
}

inline std::unique_ptr<Monster> createRandomMonster(int x = 0, int y = 0) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 2);
    switch (dist(gen)) {
        case 0: return createMonster(MonsterType::ZOMBIE, x, y);
        case 1: return createMonster(MonsterType::GHOST, x, y);
        default: return createMonster(MonsterType::SKELETON, x, y);
    }
}

#endif