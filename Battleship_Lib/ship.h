#pragma once
#include "position.h"
#include <vector>
class Ship {
private:
	int len;
	std::vector<Position> palubs;
	bool life;
public:
	Ship(int _len, std::vector<Position>& _palubs);
	~Ship();
	inline int get_len()const noexcept {
		return len;
	}
	inline const std::vector<Position>* const get_palubs()const noexcept {
		return &palubs;
	}
	void break_palub(int index);
	bool isdie()const noexcept;
};

