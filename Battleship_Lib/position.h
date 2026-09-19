#pragma once
#include <iostream>

class Position {
private:
	int x;
	int y;
	char value; // '*' 'X' '1'
public:
	Position(int _x = 1, int _y = 1, char _value = '*');
	~Position() = default;
	inline int get_x() const noexcept {
		return x;
	}
	inline int get_y() const noexcept {
		return y;
	}
	inline int get_value() const noexcept {
		return value;
	}
	inline void set_value(char _value) {
		if ((_value == '*') or (_value == 'X') or (_value == '1')) { value = _value; }
		else { throw std::logic_error("No way value"); }
	}
};
