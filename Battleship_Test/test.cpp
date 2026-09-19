#include "pch.h"
#include "position.h"
#include "ship.h"

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
//-------ship
//TEST(TestShip, TestConstructor) {
//	Position p1(1, 1, '1');
//	Position p2(1, 2, '1');
//	Position p3(1, 3, '1');
//
//	std::vector<Position> v;
//	v.push_back(p1);v.push_back(p2);v.push_back(p3);
//	Ship sh1(3, v);
//	EXPECT_EQ(sh1.get_len(), 3);
//	EXPECT_EQ(sh1.islife(), true);
//	EXPECT_EQ(sh1.get_palubs(), 3);
//
//
//}