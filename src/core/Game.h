#ifndef GAME_H
#define GAME_H

#include <memory>
#include "entities/Hero.h"
#include "rooms/Room.h"

void startBattle(Hero& hero, Monster& monster);

class Game {
public:
    Game();
    void run();

private:
    std::unique_ptr<Hero> hero;
    Room currentRoom;
    bool inBattle = false;
    std::unique_ptr<Monster>* targetMonster = nullptr;

    void chooseHero();
    void processInput(char input);
    void update();
    void render();
};

#endif
