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
	inline bool get_mode() {
		return mode;
	}
	inline void print_board(bool show) {
		my_board.print_field(show);
	}
	int human_move(int x, int y);
	bool bot_move(std::vector<Position>& moves);
	void clear_board();
	bool islose();
};