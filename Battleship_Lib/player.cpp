#include "player.h"

Player::Player(bool _mode):mode(_mode) {}

int Player::human_move(int x, int y, Gamefield& other_board){
	if (x > 10 || y > 10) { throw std::logic_error("out of range"); }
	if (x <= 0 || y <= 0) { throw std::logic_error("index <= 0"); }
	int index = (x - 1) * 10 + (y - 1);
	if (other_board.get_pole()[index].isopen()) { return 2; }
	if (other_board.attacked(x, y)) { return 1; }
	return 0;
}
bool Player::bot_move(std::vector<Position>& moves,Gamefield& other_board) {
	int x = 0, y = 0;
	if (!moves.empty() && moves.back().get_value() == '1') {
		int old_x = moves.back().get_x();
		int old_y = moves.back().get_y();
		std::vector<std::pair<int, int>> way = { {1,0},{-1,0},{0,1},{0,-1} };
		for (int i = 0; i < 4; ++i) {
			int r = rand() % 4;
			std::swap(way[i],way[r]);
		}
		for (auto w : way) {
			int new_x = old_x + w.first;
			int new_y = old_y + w.second;
			if (new_x <= 10 && new_y <= 10 && new_x >= 1 && new_y >= 1) {
				int new_index = (new_x - 1) * 10 + new_y - 1;
				if (other_board.get_pole()[new_index].isopen()) {
					continue;
				}
				x = new_x;
				y = new_y;
				break;
			}
		}
	}
	
	if (x == 0 && y == 0) {
		int target_index = (x - 1) * 10 + y - 1;
		do {
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
			target_index = (x - 1) * 10 + y - 1;
		} while (other_board.get_pole()[target_index].isopen());
	}
	int final_index = (x - 1) * 10 + y - 1;
	char cell = other_board.get_pole()[final_index].get_value();

	bool out = other_board.attacked(x, y);
	moves.push_back(Position(x, y, cell));
	return out;
}

