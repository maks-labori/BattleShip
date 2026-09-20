#include "pch.h"
#include "position.h"
#include "ship.h"
#include "gamefield.h"
#include "player.h"

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
TEST(TestShip, TestCheckshot) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(3, v);
	EXPECT_EQ(sh1.get_palubs()->operator[](0).get_value(), '1');
	EXPECT_TRUE(sh1.checkshot(1, 1));
	EXPECT_FALSE(sh1.checkshot(2, 2));
	EXPECT_EQ(sh1.get_palubs()->operator[](0).get_value(), 'X');
}
//------gamefield

TEST(TestGamefield,TestConstructor) {
	Gamefield board;
	for (int i = 0;i < 10;++i) {
		for (int j = 0;j < 10;++j) {
			EXPECT_EQ(board.get_pole(j+1,i+1).get_value(), '*');
		}
	}
}
TEST(TestGamefield, TestAddship) {
	Gamefield board;
	
	Position p1(2, 2, '1');
	Position p2(1, 2, '1');
	Position p3(3, 2, '1');

	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(3, v);
	EXPECT_EQ(board.get_pole(1, 2).get_value(), '*');
	EXPECT_EQ(board.get_pole(2, 2).get_value(), '*');
	EXPECT_EQ(board.get_pole(3, 2).get_value(), '*');
	board.addship(sh1);
	EXPECT_EQ(board.get_pole(1, 2).get_value(), '1');
	EXPECT_EQ(board.get_pole(2, 2).get_value(), '1');
	EXPECT_EQ(board.get_pole(3, 2).get_value(), '1');
	
	Position p4(6, 2, '1');
	Position p5(5, 2, '1');
	Position p6(4, 2, '1');

	std::vector<Position> v2 = { p4,p5,p6 };

	Ship sh2(3, v2);
	EXPECT_FALSE(board.addship(sh2));
	EXPECT_EQ(board.get_pole(4, 2).get_value(), '*');
	EXPECT_EQ(board.get_pole(5, 2).get_value(), '*');
	EXPECT_EQ(board.get_pole(6, 2).get_value(), '*');
}
TEST(TestGamefield, TestAttacked) {
	Gamefield board;

	Position p1(5, 6, '1');
	Position p2(6, 6, '1');
	Position p3(7, 6, '1');
	Position p4(8, 6, '1');


	std::vector<Position> v = { p1,p2,p3,p4 };

	Ship sh1(4, v);
	board.addship(sh1);
	EXPECT_EQ(board.get_pole(6, 6).get_value(), '1');
	EXPECT_TRUE(board.attacked(6, 6));
	EXPECT_EQ(board.get_pole(6, 6).get_value(), 'X');
	EXPECT_FALSE(board.attacked(6, 6));
	EXPECT_EQ(board.get_pole(6, 6).get_value(), 'X');
	EXPECT_FALSE(board.attacked(8, 8));
	EXPECT_EQ(board.get_pole(8, 8).get_value(), '*');
}
TEST(TestGamefield, TestShipsnow) {
	Gamefield board;

	Position p1(5, 6, '1');
	Position p2(6, 6, '1');
	Position p3(7, 6, '1');
	std::vector<Position> v = { p1,p2,p3 };
	
	Position r1(1, 4, '1');
	Position r2(1, 5, '1');
	Position r3(1, 6, '1');
	std::vector<Position> v2 = { r1,r2,r3 };

	Position s1(3, 3, '1');
	Position s2(3, 2, '1');
	Position s3(3, 1, '1');
	std::vector<Position> v3 = { s1,s2,s3 };

	Ship sh1(3, v);
	Ship sh2(3, v2);
	Ship sh3(3, v3);

	EXPECT_EQ(board.ships_now(), 0);
	board.addship(sh1);
	EXPECT_EQ(board.ships_now(),1);
	board.addship(sh2);
	EXPECT_EQ(board.ships_now(), 2);
	board.addship(sh3);
	EXPECT_EQ(board.ships_now(), 3);
}
TEST(TestPlayer,TestConstructor ) {
	Gamefield board1;
	Gamefield board2;
	EXPECT_NO_THROW(Player player1(board1, board2, 0));
	EXPECT_NO_THROW(Player player2(board1, board2, 1));
}

TEST(TestPlayer, TestHumanmove) {
	Gamefield board1;
	Gamefield board2;
	Player player1(board1, board2, 0);
	Player player2(board2, board1, 0);

	Position p1(5, 6, '1');
	Position p2(6, 6, '1');
	Position p3(7, 6, '1');
	std::vector<Position> v = { p1,p2,p3 };
	Ship sh1(3, v);
	board1.addship(sh1);

	EXPECT_EQ(board2.get_pole(5,6).get_value(),'*');
	EXPECT_EQ(player1.human_move(5, 6), 1);
	EXPECT_EQ(board1.get_pole(6, 6).get_value(), '1');
	EXPECT_EQ(player2.human_move(6, 6), 2);
	EXPECT_EQ(board1.get_pole(6, 6).get_value(), 'X');
	EXPECT_EQ(player1.human_move(5, 6), 0);
}

TEST(TestPlayer, TestBotmove) {
	Gamefield board1;
	Gamefield board2;
	Player bot(board1, board2, 1);
	std::vector<Position> bot_moves;
	for (int y = 1; y <= 10; ++y) {
		for (int x = 1; x <= 10; ++x) {
			if (x == 5 && y == 5) continue;
			board2.attacked(x, y);
		}
	}

	bot.bot_move(bot_moves);

	EXPECT_FALSE(bot_moves.empty());
	EXPECT_EQ(bot_moves.back().get_x(), 5);
	EXPECT_EQ(bot_moves.back().get_y(), 5);
	EXPECT_TRUE(board2.get_pole(5, 5).isopen());

	
	Gamefield board3;
	Gamefield board4;
	Player bot2(board3, board4, 1);
	std::vector<Position> bot_moves2;

	Position p1(1, 1, '1');
	Position p2(2, 1, '1');
	Position p3(3, 1, '1');
	std::vector<Position> v = { p1,p2,p3 };
	Ship sh1(3, v);
	board4.addship(sh1);

	board4.attacked(1, 2);

	Position move(1, 1, '1');
	bot_moves2.push_back(move);

	bot2.bot_move(bot_moves2);
	EXPECT_EQ(bot_moves2.back().get_x(), 2);
	EXPECT_EQ(bot_moves2.back().get_y(), 1);
	EXPECT_TRUE(board4.get_pole(2, 1).isopen());
}
