#include "position.h"

Position::Position(int _x,int _y,char _value) {
	if (_x > 0 && _y > 0) { x = _x;y = _y;set_value(_value); }
	else { throw std::logic_error("No way parametrs in constructor"); }
}