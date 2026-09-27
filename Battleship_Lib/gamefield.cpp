#include "gamefield.h"

Gamefield::Gamefield() {
	for (int i = 0;i < 10;++i) {
		for (int j = 0;j < 10;++j) {
			field.push_back(Position(i + 1, j + 1, '*'));
		}
	}
}

bool Gamefield::addship(const Ship& ship)noexcept {
	int len = ship.get_palubs().size();
	for (int i = 0;i < len;++i) {
		int x1 = ship.get_palubs()[i].get_x();
		int y1 = ship.get_palubs()[i].get_y();
		if (x1 < 1 || x1 >10 || y1 < 1 || y1 > 10) { return false; }
	}
	bool flag = true;
	if (ships.empty()) {
		ships.push_back(ship);
		for (int i = 0; i < len; ++i) {
			int x = ship.get_palubs()[i].get_x()-1;
			int y = ship.get_palubs()[i].get_y()-1;
			int index = x*10 + y;
			field[index].set_value('1');
		}
		return true;
	}
	for (int i = 0;i < len;++i) {
		int new_x = ship.get_palubs()[i].get_x() - 1;
		int new_y = ship.get_palubs()[i].get_y() - 1;
		for (int j = 0;j < ships.size();++j) {
			for (int z = 0;z < len;++z) {
				int old_x = ships[j].get_palubs()[i].get_x() - 1;
				int old_y = ships[j].get_palubs()[i].get_y() - 1;
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
		for (int i = 0; i < len; ++i) {
			int x = ship.get_palubs()[i].get_x() - 1;
			int y = ship.get_palubs()[i].get_y() - 1;
			int index = x * 10 + y;
			field[index].set_value('1');
		}
		return true;
	}
	return false;
}
void Gamefield::print_field(bool show, std::ostream& out, std::istream& in)const noexcept {
	out << "    A B C D E F G H I J\n";
	out << "  +---------------------+\n";
	for (int i = 0;i < 10;++i) {
		out << std::setw(2) << (i + 1) << "| ";
		for (int j = 0;j < 10;++j) {
			if (show || field[i*10+j].isopen()) {
				out << (char)field[i * 10 + j].get_value() << " ";
			}
			else {
				out << "~ ";
			}
		}
		out << "|\n";
	}
	out << "  +---------------------+\n";

}
bool Gamefield::attacked(int _x, int _y) {
	int index = (_x-1) * 10 + (_y-1);
	field[index].open();
	if (field[index].get_value() == '1') {
		field[index].set_value('X');
		for (int i = 0;i < ships.size();++i) {
			if (ships[i].checkshot(_x, _y)) {
				check_ships();
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
	for (int i = 0; i < ship.get_palubs().size();++i) {
		int x = ship.get_palubs()[i].get_x() - 1;
		int y = ship.get_palubs()[i].get_y() - 1;
		for (int z = y - 1;z < y + 2;++z) {
			for (int j = x - 1;j < x + 2;++j) {
				int index = (z - 1) * 10 + (j - 1);
				if (z <= 0 || j <= 0 || z > 10 || j > 10) { continue; }
				if (field[index].get_value() == 'X') { continue; }
				field[index].open();
				field[index].set_value('*');
			}
		}
	}
}

void Gamefield::check_ships()noexcept {
	for (int i = 0;i < ships.size();++i) {
		if (ships[i].isdie()) {
			ships[i].die();
			after_die_ship(ships[i]);
		}
	}
}

void Gamefield::clear_board()noexcept {
	*this = Gamefield();
}

bool Gamefield::islose()const {
	int count = ships_now();
	return (count == 0);
}
