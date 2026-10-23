#include <gtest/gtest.h>
#include "actions/Action.h"
#include "entities/Hero.h"
#include "entities/Monster.h"

// Тестовый герой: базовый урон 10, спецспособность возвращает false
class TestHero : public Hero {
public:
    TestHero() : Hero(100, 50, "Tester", 10, 0, 0) {}
    int getAttackDamage() const override { return 10; }
};

// Герой, у которого useSpecial успешен (имитация ассасина, сбежавшего из боя)
class EscapingHero : public Hero {
public:
    EscapingHero() : Hero(100, 50, "Runner", 10, 0, 0) {}
    int getAttackDamage() const override { return 10; }
    bool useSpecial() override { return true; }
};

// ---------- AttackAction ----------

TEST(AttackActionTest, ReducesMonsterHp) {
    TestHero hero;
    Monster monster(50, 0, "Dummy", 0, 0, 0);
    bool ended = false;

    testing::internal::CaptureStdout();
    AttackAction action;
    action.execute(hero, monster, ended);
    testing::internal::GetCapturedStdout();

    EXPECT_LT(monster.getHp(), 50);
    EXPECT_FALSE(ended);
}

TEST(AttackActionTest, DamageEqualsTotalDamage) {
    TestHero hero;
    Monster monster(100, 0, "Dummy", 0, 0, 0);
    bool ended = false;

    int expected = hero.getTotalDamage();

    testing::internal::CaptureStdout();
    AttackAction action;
    action.execute(hero, monster, ended);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(monster.getHp(), 100 - expected);
}

TEST(AttackActionTest, CanKillMonster) {
    TestHero hero;
    Monster monster(5, 0, "Weak", 0, 0, 0);
    bool ended = false;

    testing::internal::CaptureStdout();
    AttackAction action;
    action.execute(hero, monster, ended);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(monster.getHp(), 0);
}

// ---------- DefendAction ----------

TEST(DefendActionTest, EnablesDefending) {
    TestHero hero;
    Monster monster(50, 0, "Dummy", 0, 0, 0);
    bool ended = false;

    testing::internal::CaptureStdout();
    DefendAction action;
    action.execute(hero, monster, ended);
    testing::internal::GetCapturedStdout();

    // После защиты следующий урон должен быть уменьшен вдвое
    hero.takeDamage(20);
    EXPECT_EQ(hero.getHp(), 90);
}

// ---------- SpecialAction ----------

TEST(SpecialActionTest, DoesNotEndBattleOnFailure) {
    TestHero hero;  // useSpecial() → false
    Monster monster(50, 0, "Dummy", 0, 0, 0);
    bool ended = false;

    testing::internal::CaptureStdout();
    SpecialAction action;
    action.execute(hero, monster, ended);
    testing::internal::GetCapturedStdout();

    EXPECT_FALSE(ended);
}

TEST(SpecialActionTest, EndsBattleOnSuccess) {
    EscapingHero hero;  // useSpecial() → true
    Monster monster(50, 0, "Dummy", 0, 0, 0);
    bool ended = false;

    testing::internal::CaptureStdout();
    SpecialAction action;
    action.execute(hero, monster, ended);
    testing::internal::GetCapturedStdout();

    EXPECT_TRUE(ended);
}
