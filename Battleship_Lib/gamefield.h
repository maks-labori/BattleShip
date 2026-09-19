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
	inline const std::vector<Ship>* const get_ships() {
		return &ships;
	}
	void print_field(bool show);
	bool addship(const Ship& ship);
};
