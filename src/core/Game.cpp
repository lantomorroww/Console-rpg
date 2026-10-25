#include "core/Game.h"
#include "utils/Input.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

struct Assassin : public Hero {
    Assassin() : Hero(10, 8, "Assassin", 7, 0, 0) {}
    int getAttackDamage() const override { return 12; }
    bool useSpecial() override {
        if (rand() % 2 == 0) {
            std::cout << "Ассасин скрылся в тени!\n";
            return true;
        } else {
            std::cout << "Ассасин споткнулся! Он получит дополнительный урон.\n";
            specialDamageBonus = -5;
            return false;
        }
    }
};

struct Warrior : public Hero {
    Warrior() : Hero(15, 5, "Warrior", 8, 0, 0) {}
    int getAttackDamage() const override { return 10; }
    bool useSpecial() override {
        if (getHp() <= 0) {
            setHP(1);
            std::cout << "Рыцарь использовал Второе дыхание! HP = 1\n";
            return false;
        }
        std::cout << "Второе дыхание неактивно.\n";
        return false;
    }
};

struct Mage : public Hero {
    Mage() : Hero(8, 15, "Mage", 5, 0, 0) {}
    int getAttackDamage() const override { return 8; }
    bool useSpecial() override {
        int cost = maxMana * 0.1;
        if (getMana() < cost) {
            std::cout << "Недостаточно маны!\n";
            return false;
        }
        setMana(getMana() - cost);
        specialDamageBonus += 10;
        std::cout << "Маг запустил огненный шар! Бонус к атаке +10.\n";
        return false;
    }
};

enum class HeroType { ASSASSIN, WARRIOR, MAGE };

std::unique_ptr<Hero> createHero(HeroType type) {
    switch (type) {
        case HeroType::ASSASSIN: return std::make_unique<Assassin>();
        case HeroType::WARRIOR:  return std::make_unique<Warrior>();
        case HeroType::MAGE:     return std::make_unique<Mage>();
        default: return nullptr;
    }
}

void startBattle(Hero& hero, Monster& monster) {
    bool battleEnded = false;
    hero.resetState();

    while (!battleEnded && hero.getHp() > 0 && monster.getHp() > 0) {
        std::cout << "\n--- БОЙ ---\n";
        std::cout << "Ваше HP: " << hero.getHp() << "  |  HP монстра: " << monster.getHp() << "\n";
        std::cout << "Выберите действие:\n";
        std::cout << "1 - Атака\n";
        std::cout << "2 - Защита\n";
        std::cout << "3 - Спецспособность\n";
        std::cout << "Ваш выбор: ";

        int choice;
        std::cin >> choice;

        auto action = hero.getAction(choice);
        if (!action) {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            continue;
        }
        action->execute(hero, monster, battleEnded);
        if (battleEnded) break;

        if (monster.getHp() > 0) {
            int dmg = monster.getAttackDamage();
            hero.takeDamage(dmg);
            std::cout << "Монстр нанёс " << dmg << " урона.\n";
            hero.resetState();
        }
    }

    if (hero.getHp() <= 0) {
        std::cout << "Вы погибли... Игра окончена.\n";
        exit(0);
    } else if (monster.getHp() <= 0) {
        std::cout << "Вы победили монстра!\n";
        
    }
}

Game::Game() : currentRoom(generateRandomRoom()) {
    srand(time(nullptr));
    chooseHero();
    hero->setStartPosition(38, 19);
}

void Game::chooseHero() {
    int choice;
    std::cout << "Choose hero:\n1 - Assassin\n2 - Warrior\n3 - Mage\n";
    std::cin >> choice;
    HeroType hType;
    switch (choice) {
        case 2: hType = HeroType::WARRIOR; break;
        case 3: hType = HeroType::MAGE; break;
        default: hType = HeroType::ASSASSIN;
    }
    hero = createHero(hType);
}

void Game::render() {
    clearScreen();
    currentRoom.draw(*hero);
    if (inBattle) {
        std::cout << "\n*** БОЙ НАЧИНАЕТСЯ! ***\n";
    }
}

void Game::update() {
    if (inBattle) {
        startBattle(*hero, **targetMonster);
        currentRoom.removeDeadMonsters();
        inBattle = false;
        targetMonster = nullptr;
        return;
    }

    char input = getch();
    if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
        currentRoom.movePlayer(*hero, input);
        currentRoom.updateMonsters();
        currentRoom.checkTriggers(*hero, inBattle, targetMonster);
    } else if (input == 'q') {
        std::cout << "Игра завершена.\n";
        exit(0);
    }
}

void Game::run() {
    while (true) {
        render();
        update();
    }
}
