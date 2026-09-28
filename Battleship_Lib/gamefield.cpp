#include "gamefield.h"

Gamefield::Gamefield() {
	for (int i = 0;i < 10;++i) {
		for (int j = 0;j < 10;++j) {
			field.push_back(Position(i + 1, j + 1, '*'));
		}
	}
}

bool Gamefield::addship(const Ship& ship)noexcept {
	int len = ship.get_palubs().size(); //check coords in ship
	if (!ship.is_valid()) { return false; }
	if (ships.empty()) { //empty - true
		ships.push_back(ship);
		for (int i = 0; i < len; ++i) {
			int index = ship.get_palubs()[i].get_index();
			field[index].set_value('1');
		}
		return true;
	}
	int count_ships = ships.size();
	for (int i = 0;i < len;++i) { //near - false
		int new_x = ship.get_palubs()[i].get_x();
		int new_y = ship.get_palubs()[i].get_y();
		for (int j = 0;j < count_ships;++j) {
			int old_len = ships[j].get_palubs().size();
			for (int z = 0;z < old_len;++z) {
				int old_x = ships[j].get_palubs()[z].get_x();
				int old_y = ships[j].get_palubs()[z].get_y();
				if (abs(new_x - old_x) <= 1 && abs(new_y - old_y) <= 1) {
					return false;
				}
				
			}
		}
	}
	ships.push_back(ship); //add ship and update field
	for (int i = 0; i < len; ++i) {
		int index = ship.get_palubs()[i].get_index();
		field[index].set_value('1');
	}
	return true;
}
void Gamefield::print_field(bool show, std::ostream& out, std::istream& in)const noexcept {
	out << "    A B C D E F G H I J\n";
	out << "  +---------------------+\n";
	for (int i = 0;i < 10;++i) {
		out << std::setw(2) << (i + 1) << "| ";
		for (int j = 0;j < 10;++j) {
			int index = j * 10 + i;
			if (show || field[index].isopen()) {
				out << (char)field[index].get_value() << " ";
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
	int count_ships = ships.size();
	int total = count_ships;
	for (int i = 0;i < count_ships;++i) {
		if (ships[i].isdie()) { total--; }
	}
	return total;
}
void Gamefield::after_die_ship(const Ship& ship)noexcept {
	int count_palubs = ship.get_palubs().size();
	for (int i = 0; i < count_palubs;++i) {
		int x = ship.get_palubs()[i].get_x();
		int y = ship.get_palubs()[i].get_y();
		for (int cur_y = y - 1;cur_y < y + 2;++cur_y) {
			for (int cur_x= x - 1;cur_x < x + 2;++cur_x) {
				if (cur_y < 1|| cur_x < 1 || cur_y > 10 ||cur_x > 10) { continue; }
				int index = Position(cur_x, cur_y).get_index();
				if (field[index].get_value() == 'X') { continue; }
				field[index].open();
				field[index].set_value('*');
			}
		}
	}
}

void Gamefield::check_ships()noexcept {
	int count_ships = ships.size();
	for (int i = 0;i < count_ships;++i) {
		if (ships[i].isdie()) {
			ships[i].die();
			after_die_ship(ships[i]);
		}
	}
}

void Gamefield::clear_board()noexcept {
	*this = Gamefield();
}

bool Gamefield::islose()const noexcept {
	int count = ships_now();
	return (count == 0);
}
