#pragma once
#include "ship.h"
#include <cmath>
#include <iomanip>

class Gamefield {
private:
	static const int FIELD_SIZE = 10;
	std::vector<Ship> ships;
	Position field[FIELD_SIZE][FIELD_SIZE];
public:
	Gamefield();
	~Gamefield();
	inline const std::vector<Ship>* const get_ships() const noexcept {
		return &ships;
	}
	inline const Position& get_pole(int _x, int _y) {
		if (_x > FIELD_SIZE || _y > FIELD_SIZE) { throw std::logic_error("out of range"); }
		if (_x <= 0 || _y <= 0) { throw std::logic_error("index <= 0"); }
		return (field[_y-1][_x-1]);
	}
	void print_field(bool show)noexcept;
	bool addship(const Ship& ship)noexcept;
	bool attacked(int _x, int _y);
	int ships_now()const noexcept;
	void after_die_ship(Ship& ship)noexcept;
	void check_ships();
};
