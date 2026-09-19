#include "position.h"

Position::Position(int _x,int _y,char _value) {
	if (_x > 0 and _y > 0 and ((_value == '*') or (_value == 'X') or (_value == '1'))) { x = _x;y = _y;value = _value; }
	else { throw std::logic_error("No way parametrs in constructor"); }
}