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
bool Gamefield::addship(const Ship& ship)noexcept {
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
				int old_x = ships[j].get_palubs()->operator[](z).get_x() - 1;
				int old_y = ships[j].get_palubs()->operator[](z).get_y() - 1;

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
void Gamefield::print_field(bool show)noexcept {
	std::cout << "    A B C D E F G H I J\n";
	std::cout << "  +---------------------+\n";
	for (int i = 0;i < FIELD_SIZE;++i) {
		std::cout << std::setw(2) << (i + 1) << "| ";
		for (int j = 0;j < FIELD_SIZE;++j) {
			if (show || field[i][j].isopen()) {
				std::cout << (char)field[i][j].get_value() << " ";
			}
			else {
				std::cout << "~ ";
			}
		}
		std::cout << "|\n";
	}
	std::cout << "  +---------------------+\n";

}
bool Gamefield::attacked(int _x, int _y) {
	field[_y - 1][_x - 1].open();
	if (field[_y - 1][_x - 1].get_value() == '1') {
		field[_y - 1][_x - 1].set_value('X');
		for (int i = 0;i < ships.size();++i) {
			if (ships[i].checkshot(_x, _y)) {
				break;
			}
		}
		return true;
	}
	return false;
}

int Gamefield::ships_now()const noexcept{
	int total = ships.size();
	for (int i = 0;i < ships.size();++i) {
		if (ships[i].isdie()) { total--; }
	}
	return total;
}
void Gamefield::after_die_ship(Ship& ship)noexcept {
	for (int i = 0; i < ship.get_len();++i) {
		int x = ship.get_palubs()->operator[](i).get_x();
		int y = ship.get_palubs()->operator[](i).get_y();
		for (int z = y - 1;z < y + 1;++z) {
			for (int j = x - 1;i < x + 1;++j) {
				if (z <= 0 || j <= 0 || z > 10 || j > 10) { continue; }
				if (field[z - 1][j - 1].get_value() == 'X') { continue; }
				field[z - 1][j - 1].open();
				field[z - 1][j - 1].set_value('X');
			}
		}
	}
}

void Gamefield::check_ships() {
	for (int i = 0;i < ships.size();++i) {
		if (ships[i].isdie()) {
			ships[i].die();
			after_die_ship(ships[i]);
		}
	}
}