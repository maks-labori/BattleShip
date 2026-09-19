#include "gamefield.h"

Gamefield::Gamefield() {
	for (int i = 0;i < FIELD_SIZE;++i) {
		for (int j = 0;j < FIELD_SIZE;++j) {
			this->field[i][j] = Position(i + 1, j + 1, '*');
		}
	}
}
Gamefield::~Gamefield() {
	ships.clear();
	ships.shrink_to_fit();
}
bool Gamefield::addship(const Ship& ship) {
	bool flag = true;
	if (ships.empty()) {
		ships.push_back(ship);
		for (int i = 0; i < ship.get_len(); ++i) {
			int x = ship.get_palubs()->operator[](i).get_x() - 1;
			int y = ship.get_palubs()->operator[](i).get_y() - 1;
			this->field[y][x].set_value('1');
		}
		return true;
	}
	for (int i = 0;i < ship.get_len();++i) {
		int new_x = ship.get_palubs()->operator[](i).get_x() - 1;
		int new_y = ship.get_palubs()->operator[](i).get_y() - 1;
		for (int j = 0;j < ships.size();++j) {
			for (int z = 0;z < ships[j].get_len();++z) {
				int old_x = ships[j].get_palubs()->operator[](i).get_x() - 1;
				int old_y = ships[j].get_palubs()->operator[](i).get_y() - 1;

				if (abs(new_x - old_x) <= 1 && abs(new_y - old_y) <= 1) {
					flag = false;
					break;
				}
				
			}
			if (!flag) { break; }
		}
		if (!flag) { break; }
	}
	if (flag) {
		ships.push_back(ship);
		for (int i = 0; i < ship.get_len(); ++i) {
			int x = ship.get_palubs()->operator[](i).get_x() - 1;
			int y = ship.get_palubs()->operator[](i).get_y() - 1;
			this->field[y][x].set_value('1');
		}
		return true;
	}
	return false;
}
void Gamefield::print_field(bool show) {
	std::cout << "    A B C D E F G H I J\n";
	std::cout << "  +---------------------+\n";
	for (int i = 0;i < FIELD_SIZE;++i) {
		std::cout << std::setw(2) << (i + 1) << "| ";
		for (int j = 0;j < FIELD_SIZE;++j) {
			if (show) {
				std::cout << (char)field[i][j].get_value() << " ";
			}
			else {
				std::cout << "~";
			}
		}
		std::cout << "|\n";
	}
	std::cout << "  +---------------------+\n";

}