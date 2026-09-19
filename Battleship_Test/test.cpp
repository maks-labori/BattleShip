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
TEST(TestShip, TestConstructor) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };
	Ship sh1(3, v);
	
	EXPECT_EQ(sh1.get_len(), 3);
	EXPECT_EQ(sh1.isdie(), false);

	for (int i = 0;i < v.size();i++) {
		EXPECT_EQ(v[i].get_x(), sh1.get_palubs()->operator[](i).get_x());
		EXPECT_EQ(v[i].get_y(), sh1.get_palubs()->operator[](i).get_y());
		EXPECT_EQ(v[i].get_value(), sh1.get_palubs()->operator[](i).get_value());
	}
}
TEST(TestShip, TestConstructorThrow) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };

	EXPECT_THROW(Ship sh1(2,v),std::logic_error);
	v.push_back(p1);v.push_back(p2);
	EXPECT_THROW(Ship sh1(5, v), std::logic_error);

	Position g1(2, 1, '1');
	Position g2(1, 2, '1');
	Position g3(1, 3, '1');

	std::vector<Position> v2 = { g1,g2,g3 };

	EXPECT_THROW(Ship sh1(3, v2), std::logic_error);

	Position h1(1, 1, '*');
	Position h2(1, 2, '1');
	Position h3(1, 3, '1');

	std::vector<Position> v3 = { h1,h2,h3 };

	EXPECT_THROW(Ship sh1(3, v3), std::logic_error);
}
TEST(TestShip, TestBreakPalub) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(3, v);
	EXPECT_EQ(sh1.get_palubs()->operator[](0).get_value(), '1');
	sh1.break_palub(0);
	EXPECT_EQ(sh1.get_palubs()->operator[](0).get_value(), 'X');

	EXPECT_EQ(sh1.get_palubs()->operator[](1).get_value(), '1');
	sh1.break_palub(1);
	EXPECT_EQ(sh1.get_palubs()->operator[](1).get_value(), 'X');

	EXPECT_EQ(sh1.get_palubs()->operator[](2).get_value(), '1');
	sh1.break_palub(2);
	EXPECT_EQ(sh1.get_palubs()->operator[](2).get_value(), 'X');

	EXPECT_TRUE(sh1.isdie());
}