#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>
#include "entities/Monster.h"
#include "entities/Hero.h"

enum class RoomType { EMPTY, MONSTER_CHEST, MONSTER_CHEST_TRAP, MAXIMAL };

class Room {
private:
    int chest;
    int objects;
    std::vector<std::unique_ptr<Monster>> monsters;
    bool chestOpened[2] = {false, false};
    bool trapTriggered[2] = {false, false};

public:
    Room();
    Room(int chestCount, int objectsCount, std::vector<std::unique_ptr<Monster>> mon);
    ~Room();

    void showRoom() const;
    void draw(const Hero& hero) const;

    bool isWalkable(int x, int y) const;
    bool isOccupied(int x, int y) const;

    void movePlayer(Hero& hero, char direction);
    void checkTriggers(Hero& hero, bool& battleStarted, std::unique_ptr<Monster>*& targetMonster);
    void updateMonsters(); // патрулирование
    void removeDeadMonsters();
    Room(const Room&) = delete;
Room& operator=(const Room&) = delete;

Room(Room&&) = default;
Room& operator=(Room&&) = default;
};

Room generateRandomRoom();

#endif
