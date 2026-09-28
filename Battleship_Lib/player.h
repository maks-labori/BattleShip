#pragma once
#include "gamefield.h"
#include <algorithm>
class Player {
private:
	bool mode; // 0 - компьютер , 1 - человек
public:
	Player(bool _mode);
	~Player() = default;
	inline bool get_mode()const noexcept {
		return mode;
	}
	int human_move(int x, int y,Gamefield& other_board);
	bool bot_move(std::vector<Position>& moves,Gamefield& other_board);
};