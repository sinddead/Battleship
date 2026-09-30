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

TEST(PositionTest, NegativeSetters) {
    EXPECT_ANY_THROW(Position p(-2,3));
}

TEST(PositionTest, NegativeConstruct) {
    Position p;
    EXPECT_ANY_THROW(p.setx(-6));
}

TEST(PositionTest, EqualityTrue) {
    EXPECT_TRUE(Position(1, 2) == Position(1, 2));
}

TEST(PositionTest, EqualityFalse) {
    EXPECT_FALSE(Position(1, 2) == Position(2, 2));
}

TEST(PositionTest, InequalityTrue) {
    EXPECT_TRUE(Position(1, 2) != Position(2, 1));
}

TEST(PositionTest, InequalityFalse) {
    EXPECT_FALSE(Position(1, 2) != Position(1, 2));
}