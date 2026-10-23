#include <gtest/gtest.h>
#include "rooms/Room.h"

TEST(RoomTest, WallsAreNotWalkable) {
    Room room(0, 0, {});
    EXPECT_FALSE(room.isWalkable(1, 10));
    EXPECT_FALSE(room.isWalkable(38, 1));
}

TEST(RoomTest, CenterIsWalkable) {
    Room room(0, 0, {});
    EXPECT_TRUE(room.isWalkable(38, 10));
}

TEST(RoomTest, DoorIsWalkable) {
    Room room(0, 0, {});
    EXPECT_TRUE(room.isWalkable(38, 20));
    EXPECT_TRUE(room.isWalkable(39, 20));
}

TEST(RoomTest, OutsideIsNotWalkable) {
    Room room(0, 0, {});
    EXPECT_FALSE(room.isWalkable(0, 10));
    EXPECT_FALSE(room.isWalkable(77, 10));
    EXPECT_FALSE(room.isWalkable(38, 0));
    EXPECT_FALSE(room.isWalkable(38, 21));
}
