#pragma once
#include "gamefield.h"
#include <algorithm>
class Player {
private:
	Gamefield& my_board;
	Gamefield& other_board;
	bool mode; // 0 - компьютер , 1 - человек
public:
	Player(Gamefield& _my_board,Gamefield& _other_board, bool _mode);
	~Player() = default;
	inline bool addship_board(const Ship& ship)noexcept {
		return (my_board.addship(ship));
	}
	int human_move(int x, int y);
	void bot_move(std::vector<Position>& moves);
};