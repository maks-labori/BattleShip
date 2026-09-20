#include "player.h"

Player::Player(const Gamefield& _my_board, const Gamefield& _other_board, bool _mode):my_board(_my_board),other_board(_other_board),mode(_mode) {}

int Player::human_move(int x, int y){
	if (x > 10 || y > 10) { throw std::logic_error("out of range"); }
	if (x <= 0 || y <= 0) { throw std::logic_error("index <= 0"); }
	if (other_board.get_pole(x, y).isopen()) { return 0; }
	if (other_board.attacked(x, y)) { return 2; }
	return 1;
}
void Player::bot_move(std::vector<Position>& moves) {
	int x = 0, y = 0;
	if (!moves.empty() && moves.back().get_value() == '1') {
		int old_x = moves.back().get_x();
		int old_y = moves.back().get_y();
		int way[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
		for (int i = 0; i < 4; ++i) {
			int r = rand() % 4;
			std::swap(way[i],way[r]);
		}
		for (auto w : way) {
			int new_x = old_x + w[0];
			int new_y = old_y + w[1];
			if (new_x <= 10 && new_y <= 10 && new_x >= 1 && new_y >= 1) {
				if (other_board.get_pole(new_x, new_y).isopen()) {
					continue;
				}
				x = new_x;
				y = new_y;
				break;
			}
		}
	}
	if (x == 0 && y == 0) {
		do {
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
		} while (other_board.get_pole(x, y).isopen());
	}

	char cell = other_board.get_pole(x, y).get_value();

	other_board.attacked(x, y);
	moves.push_back(Position(x, y, cell));
}