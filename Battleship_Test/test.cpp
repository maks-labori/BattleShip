#include "pch.h"
#include "position.h"
#include "ship.h"
#include "gamefield.h"
#include "player.h"
#include "game.h"
#include <gtest/gtest.h>
#include <fstream>

#define POSITION_TEST
#define SHIP_TEST
#define GAMEFIELD_TEST
#define PLAYER_TEST
#define GAME_TEST

#ifdef POSITION_TEST
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
#endif

#ifdef SHIP_TEST
TEST(TestShip, TestConstructor) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };
	Ship sh1(v);
	
	EXPECT_EQ(sh1.isdie(), false);

	for (int i = 0;i < v.size();i++) {
		EXPECT_EQ(v[i].get_x(), sh1.get_palubs()[i].get_x());
		EXPECT_EQ(v[i].get_y(), sh1.get_palubs()[i].get_y());
		EXPECT_EQ(v[i].get_value(), sh1.get_palubs()[i].get_value());
	}
}

TEST(TestShip, TestConstructorThrow) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');
	Position p4(1, 4, '1');
	Position p5(1, 4, '1');

	std::vector<Position> v = { p1,p2,p3 };
	std::vector<Position> v5 = { p1,p2,p3,p4,p5 };
	EXPECT_NO_THROW(Ship sh1(v));
	v.push_back(p1);v.push_back(p2);
	EXPECT_THROW(Ship sh1(v),std::logic_error);
	EXPECT_THROW(Ship sh1(v5), std::logic_error);

	Position g1(2, 1, '1');
	Position g2(1, 2, '1');
	Position g3(1, 3, '1');

	std::vector<Position> v2 = { g1,g2,g3 };

	EXPECT_THROW(Ship sh1(v2), std::logic_error);

	Position h1(1, 1, '*');
	Position h2(1, 2, '1');
	Position h3(1, 3, '1');

	std::vector<Position> v3 = { h1,h2,h3 };

	EXPECT_THROW(Ship sh1(v3), std::logic_error);
}

TEST(TestShip, TestBreakPalub) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(v);
	EXPECT_EQ(sh1.get_palubs()[0].get_value(), '1');
	sh1.break_palub(0);
	EXPECT_EQ(sh1.get_palubs()[0].get_value(), 'X');

	EXPECT_EQ(sh1.get_palubs()[1].get_value(), '1');
	sh1.break_palub(1);
	EXPECT_EQ(sh1.get_palubs()[1].get_value(), 'X');

	EXPECT_EQ(sh1.get_palubs()[2].get_value(), '1');
	sh1.break_palub(2);
	EXPECT_EQ(sh1.get_palubs()[2].get_value(), 'X');

	EXPECT_TRUE(sh1.isdie());
}

TEST(TestShip, TestCheckshot) {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');

	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(v);
	EXPECT_EQ(sh1.get_palubs()[0].get_value(), '1');
	EXPECT_TRUE(sh1.checkshot(1, 1));
	EXPECT_FALSE(sh1.checkshot(2, 2));
	EXPECT_EQ(sh1.get_palubs()[0].get_value(), 'X');
}
#endif


#ifdef GAMEFIELD_TEST

class Test_Gamefield : public ::testing::Test {
protected:
	Gamefield board;
};

TEST_F(Test_Gamefield,TestConstructor) {
	for (int i = 0;i < 10;++i) {
		for (int j = 0;j < 10;++j) {
			int index = j * 10 + i;
			EXPECT_EQ(board.get_pole()[index].get_value(), '*');
		}
	}
}

TEST_F(Test_Gamefield, TestAddship) {	
	Position p1(2, 2, '1');
	Position p2(1, 2, '1');
	Position p3(3, 2, '1');

	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(v);
	EXPECT_EQ(board.get_pole()[1].get_value(), '*');
	EXPECT_EQ(board.get_pole()[11].get_value(), '*');
	EXPECT_EQ(board.get_pole()[21].get_value(), '*');
	board.addship(sh1);
	EXPECT_EQ(board.get_pole()[1].get_value(), '1');
	EXPECT_EQ(board.get_pole()[11].get_value(), '1');
	EXPECT_EQ(board.get_pole()[21].get_value(), '1');
	
	Position p4(6, 2, '1');
	Position p5(5, 2, '1');
	Position p6(4, 2, '1');

	std::vector<Position> v2 = { p4,p5,p6 };

	Ship sh2(v2);
	EXPECT_FALSE(board.addship(sh2));
	EXPECT_EQ(board.get_pole()[31].get_value(), '*');
	EXPECT_EQ(board.get_pole()[41].get_value(), '*');
	EXPECT_EQ(board.get_pole()[51].get_value(), '*');
}

TEST_F(Test_Gamefield, TestAttacked) {

	Position p1(5, 6, '1');
	Position p2(6, 6, '1');
	Position p3(7, 6, '1');
	Position p4(8, 6, '1');

	std::vector<Position> v = { p1,p2,p3,p4 };

	Ship sh1(v);
	board.addship(sh1);
	EXPECT_EQ(board.get_pole()[55].get_value(), '1');
	EXPECT_TRUE(board.attacked(6, 6));
	EXPECT_EQ(board.get_pole()[55].get_value(), 'X');
	EXPECT_FALSE(board.attacked(6, 6));
	EXPECT_EQ(board.get_pole()[55].get_value(), 'X');
	EXPECT_FALSE(board.attacked(8, 8));
	EXPECT_EQ(board.get_pole()[77].get_value(), '*');
}

TEST_F(Test_Gamefield, TestShipsnow) {

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

	Ship sh1(v);
	Ship sh2(v2);
	Ship sh3(v3);

	EXPECT_EQ(board.ships_now(), 0);
	board.addship(sh1);
	EXPECT_EQ(board.ships_now(),1);
	board.addship(sh2);
	EXPECT_EQ(board.ships_now(), 2);
	board.addship(sh3);
	EXPECT_EQ(board.ships_now(), 3);
}
#endif

#ifdef PLAYER_TEST

TEST(TestPlayer,TestConstructor ) {
	Player player(0);
	EXPECT_EQ(player.get_mode(), 0);
}

TEST(TestPlayer, TestHumanmove) {
	Gamefield board1;
	Gamefield board2;
	Player player1(0);
	Player player2(0);

	Position p1(5, 6, '1');
	Position p2(6, 6, '1');
	Position p3(7, 6, '1');
	std::vector<Position> v = { p1,p2,p3 };
	Ship sh1(v);
	board1.addship(sh1);

	EXPECT_EQ(board2.get_pole()[45].get_value(), '*');
	EXPECT_EQ(player1.human_move(5, 6,board2), 0);
	EXPECT_EQ(board1.get_pole()[45].get_value(), '1');
	EXPECT_EQ(player2.human_move(6, 6,board1), 1);
	EXPECT_EQ(board1.get_pole()[55].get_value(), 'X');
	EXPECT_EQ(player1.human_move(5, 6,board2), 2);
}

TEST(TestPlayer, TestBotmove) {
	Gamefield board2;
	Player bot(1);
	std::vector<Position> bot_moves;
	for (int y = 1; y <= 10; ++y) {
		for (int x = 1; x <= 10; ++x) {
			if (x == 5 && y == 5) continue;
			board2.attacked(x, y);
		}
	}

	bot.bot_move(bot_moves,board2);

	EXPECT_FALSE(bot_moves.empty());
	EXPECT_EQ(bot_moves.back().get_x(), 5);
	EXPECT_EQ(bot_moves.back().get_y(), 5);
	EXPECT_TRUE(board2.get_pole()[44].isopen());

	Gamefield board4;
	Player bot2(1);
	std::vector<Position> bot_moves2;

	Position p1(1, 1, '1');
	Position p2(2, 1, '1');
	Position p3(3, 1, '1');
	std::vector<Position> v = { p1,p2,p3 };
	Ship sh1(v);
	board4.addship(sh1);

	board4.attacked(1, 2);

	Position move(1, 1, '1');
	bot_moves2.push_back(move);

	bot2.bot_move(bot_moves2,board4);
	EXPECT_EQ(bot_moves2.back().get_x(), 2);
	EXPECT_EQ(bot_moves2.back().get_y(), 1);
	EXPECT_TRUE(board4.get_pole()[10].isopen());
}
#endif

#ifdef GAME_TEST

class GameTest : public ::testing::Test {
protected:
	Game game;
};

TEST_F(GameTest, TestInputhuman) {
	std::stringstream input("1\n");
	std::stringstream output;

	bool mode = game.input_mode(output,input);

	EXPECT_TRUE(mode);
	EXPECT_EQ(output.str(), "Choice mode (0 - comp,1 - human): ");
}

TEST_F(GameTest, TestInputcomp) {
	std::stringstream input("0\n");
	std::stringstream output;

	bool mode = game.input_mode(output,input);

	EXPECT_FALSE(mode);
	EXPECT_EQ(output.str(), "Choice mode (0 - comp,1 - human): ");
}

TEST_F(GameTest, Testthrowinput) {
	std::stringstream input("abc\n1\n");
	std::stringstream output;

	bool mode = game.input_mode(output,input);

	EXPECT_TRUE(mode);
	EXPECT_EQ(output.str(), "Choice mode (0 - comp,1 - human): incorrect inputChoice mode (0 - comp,1 - human): ");
}

TEST_F(GameTest, Testinputcord) {
	std::stringstream input("A 1\n");
	std::stringstream output;

	Position coords = game.input_coords(output,input);

	EXPECT_EQ(coords.get_x(), 1);
	EXPECT_EQ(coords.get_y(), 1);
}

TEST_F(GameTest, Testthrowinputcord) {
	std::stringstream input("Z 5\nB 3\n");
	std::stringstream output;

	Position coords = game.input_coords(output,input);
	EXPECT_EQ(output.str(), "Input coords (advices : A 10): Incorrect input (letter from A to J), try again\nInput coords (advices : A 10): ");
}

TEST_F(GameTest, invalidinputcoords) {
	std::stringstream input("C 15\nC 7\n");
	std::stringstream output;

	Position coords = game.input_coords(output,input);
	EXPECT_EQ(output.str(), "Input coords (advices : A 10): Incorrect input (y from 1 to 10), try again\nInput coords (advices : A 10): ");
}

TEST_F(GameTest, invalidinputcoords2) {
	std::stringstream input("A abc\nA 4\n");
	std::stringstream output;

	Position coords = game.input_coords(output,input);
	EXPECT_EQ(output.str(), "Input coords (advices : A 10): Incorrect input (invalid stoi argument), try again\nInput coords (advices : A 10): ");
}

TEST_F(GameTest, Testcompinit) {
	Gamefield b1;
	Player bot_player(0);
	std::stringstream output;
	std::stringstream input;
	game.init_ships(b1,bot_player, output,input);

	EXPECT_EQ(output.str(), "computer choices ships\ncomputer finish choice ships\n");
}

TEST_F(GameTest, Testhumaninit) {
	Gamefield b2;
	Player human_player(1);
	std::stringstream output;
	std::stringstream input(
		"A 1 H\n"  
		"A 3 H\n" 
		"E 3 H\n"  
		"A 5 H\n"  
		"D 5 H\n"  
		"G 5 H\n"  
		"A 7 H\n"  
		"C 7 H\n"  
		"E 7 H\n"  
		"G 7 H\n"  
	);
	EXPECT_NO_THROW(game.init_ships(b2, human_player, output, input));
}
#endif