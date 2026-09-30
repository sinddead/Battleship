#include "pch.h"
#include "Battlelib.h"

TEST(PositionTest, DefaultConstructor) {
    Position p;
    EXPECT_EQ(p.getx(), 1);
    EXPECT_EQ(p.gety(), 1);
}

TEST(PositionTest, ParametricConstructor) {
    Position p(3, 5);
    EXPECT_EQ(p.getx(), 3);
    EXPECT_EQ(p.gety(), 5);
}

TEST(PositionTest, CopyConstructor) {
    Position a(1, 2);
    Position b(a);
    EXPECT_EQ(b.getx(), 1);
    EXPECT_EQ(b.gety(), 2);
    EXPECT_EQ(a, b);
}

TEST(PositionTest, Setters) {
    Position p;
    p.setx(6);
    p.sety(7);
    EXPECT_EQ(p.getx(), 6);
    EXPECT_EQ(p.gety(), 7);
}

TEST(PositionTest, EqualityTrue) {
    EXPECT_TRUE(Position(1, 2) == Position(1, 2));
}

TEST(PositionTest, InequalityTrue) {
    EXPECT_TRUE(Position(1, 2) != Position(2, 1));
}

TEST(WarshipTest, ShipType) {
    Warship w(Ship::wsl3, false, Position(0, 0));
    EXPECT_EQ(w.getship(), Ship::wsl3);
}

TEST(WarshipTest, FlagsTest) {
    Warship a(Ship::wsl2, false, Position(0, 0));
    EXPECT_FALSE(a.getvertical());
}

TEST(WarshipTest, PositionCorrect) {
    Position pos(4, 7);
    Warship w(Ship::wsl2, false, pos);
    EXPECT_EQ(w.getpos(), pos);
    EXPECT_EQ(w.getpos().getx(), 4);
    EXPECT_EQ(w.getpos().gety(), 7);
}

TEST(WarshipTest, HorizontalCellsGoRight) {
    Warship w(Ship::wsl3, false, Position(2, 5));
    const auto& cells = w.getcells();
    ASSERT_EQ(cells.size(), 3u);
    EXPECT_EQ(cells[0], Position(2, 5));
    EXPECT_EQ(cells[1], Position(3, 5));
    EXPECT_EQ(cells[2], Position(4, 5));
}

TEST(WarshipTest, VerticalCellsGoDown) {
    Warship w(Ship::wsl3, true, Position(2, 5));
    const auto& cells = w.getcells();
    ASSERT_EQ(cells.size(), 3u);
    EXPECT_EQ(cells[0], Position(2, 5));
    EXPECT_EQ(cells[1], Position(2, 6));
    EXPECT_EQ(cells[2], Position(2, 7));
}
