#include "pch.h"
#include "position.h"

TEST(TestPosition, TestConstuctor) {
	Position p1(6, 9, 'X');
	EXPECT_EQ(p1.get_x(), 6);
	EXPECT_EQ(p1.get_y(), 9);
	EXPECT_EQ(p1.get_value(), 'X');

	Position p2(2, 6);
	EXPECT_EQ(p2.get_x(), 2);
	EXPECT_EQ(p2.get_y(), 6);
	EXPECT_EQ(p2.get_value(), '*');
}
TEST(TestPosition, TestConstuctorThrow) {
	EXPECT_THROW([]() {Position p1(-4, 7, '*');}(), std::logic_error);
	EXPECT_THROW([]() {Position p1(7, -4, '*');}(), std::logic_error);
	EXPECT_THROW([]() {Position p1(1, 7, 'h');}(), std::logic_error);
}
TEST(TestPosition, TestSet) {
	Position p1(2, 2, '*');
	EXPECT_EQ(p1.get_value(), '*');
	p1.set_value('1');
	EXPECT_EQ(p1.get_value(), '1');
	EXPECT_THROW(p1.set_value('G'), std::logic_error);
}