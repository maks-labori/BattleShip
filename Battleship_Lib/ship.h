#pragma once
#include "position.h"
#include <vector>
class Ship {
private:
	std::vector<Position> palubs;
	bool life;
public:
	Ship(const std::vector<Position>& _palubs);
	~Ship() = default;
	inline const std::vector<Position>& get_palubs()const noexcept {
		return palubs;
	}
	inline void die() noexcept{
		life = false;
	}
	inline void set_palubs(int index,char value) {
		if (index >= 0 && index <= 4) {
			palubs[index].set_value(value);
		}
	}
	bool checkshot(int _x, int _y);
	void break_palub(int index);
	bool isdie()const noexcept;
	bool is_valid()const noexcept;
};

