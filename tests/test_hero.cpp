#include <gtest/gtest.h>
#include "entities/Hero.h"

class TestHero : public Hero {
public:
    TestHero() : Hero(100, 50, "Tester", 10, 0, 0) {}
    int getAttackDamage() const override { return 10; }
};

TEST(HeroTest, TakeDamageReducesHp) {
    TestHero hero;
    hero.takeDamage(20);
    EXPECT_EQ(hero.getHp(), 80);
}

TEST(HeroTest, DefendHalvesDamage) {
    TestHero hero;
    hero.defend();
    hero.takeDamage(30);
    EXPECT_EQ(hero.getHp(), 85);
}

TEST(HeroTest, HpDoesNotGoBelowZero) {
    TestHero hero;
    hero.takeDamage(150);
    EXPECT_EQ(hero.getHp(), 0);
}

TEST(HeroTest, MoveChangesPosition) {
    TestHero hero;
    hero.setStartPosition(10, 10);
    hero.move('w');
    EXPECT_EQ(hero.getX(), 10);
    EXPECT_EQ(hero.getY(), 9);
}

TEST(HeroTest, AddHpWorks) {
    TestHero hero;
    hero.addHP(-30);
    EXPECT_EQ(hero.getHp(), 70);
    hero.addHP(-100);
    EXPECT_EQ(hero.getHp(), 0);
}