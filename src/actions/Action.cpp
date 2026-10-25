#include "actions/Action.h"
#include "entities/Hero.h"
#include "entities/Monster.h"
#include <iostream>

void AttackAction::execute(Hero& hero, Monster& monster, bool& battleEnded) {
    int damage = hero.getTotalDamage();
    monster.takeDamage(damage);
    std::cout << "Вы нанесли " << damage << " урона монстру.\n";
    hero.resetState(); 
}

void DefendAction::execute(Hero& hero, Monster& monster, bool& battleEnded) {
    hero.defend();
    std::cout << "Вы защищаетесь.\n";
}

void SpecialAction::execute(Hero& hero, Monster& monster, bool& battleEnded) {
    if (hero.useSpecial()) {
        battleEnded = true;
        std::cout << "Вы успешно применили специальное умение!\n";
    } else {
        std::cout << "Специальное умение применено.\n";
    }
}
