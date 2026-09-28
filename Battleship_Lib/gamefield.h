#pragma once
#include "ship.h"
#include <cmath>
#include <iomanip>
#include <sstream>

class Gamefield {
private:
	std::vector<Ship> ships;
	std::vector<Position> field;
public:
	Gamefield();
	~Gamefield() = default;
	inline const std::vector<Ship>& get_ships() const noexcept {
		return ships;
	}
	inline const std::vector<Position>& get_pole() {
		return field;
	}
	void print_field(bool show,std::ostream& out,std::istream& in)const noexcept;
	bool addship(const Ship& ship)noexcept;
	bool attacked(int _x, int _y);
	int ships_now()const noexcept;
	void after_die_ship(const Ship& ship)noexcept;
	void check_ships()noexcept;
	void clear_board()noexcept;
	bool islose()const noexcept;
};
