#ifndef ACTION_H
#define ACTION_H

class Hero;
class Monster;

class Action {
public:
    virtual void execute(Hero& hero, Monster& monster, bool& battleEnded) = 0;
    virtual ~Action() = default;
};

class AttackAction : public Action {
public:
    void execute(Hero& hero, Monster& monster, bool& battleEnded) override;
};

class DefendAction : public Action {
public:
    void execute(Hero& hero, Monster& monster, bool& battleEnded) override;
};

class SpecialAction : public Action {
public:
    void execute(Hero& hero, Monster& monster, bool& battleEnded) override;
};

#endif