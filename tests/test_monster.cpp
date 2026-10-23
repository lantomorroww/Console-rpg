#include <gtest/gtest.h>
#include "entities/Monster.h"

TEST(MonsterTest, TakeDamageReducesHp) {
    Monster m(50, 0, "Dummy", 0, 0, 0);
    m.takeDamage(15);
    EXPECT_EQ(m.getHp(), 35);
}

TEST(MonsterTest, HpDoesNotGoBelowZero) {
    Monster m(10, 0, "Dummy", 0, 0, 0);
    m.takeDamage(999);
    EXPECT_EQ(m.getHp(), 0);
}

TEST(MonsterTest, PositionIsSettable) {
    Monster m(10, 0, "Dummy", 0, 0, 0);
    m.setPosition(5, 7);
    EXPECT_EQ(m.getX(), 5);
    EXPECT_EQ(m.getY(), 7);
}
