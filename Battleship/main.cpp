#include "gamefield.h"

int main() {
	Position p1(1, 1, '1');
	Position p2(1, 2, '1');
	Position p3(1, 3, '1');
	std::vector<Position> v = { p1,p2,p3 };

	Ship sh1(3, v);

	Position g1(9, 9, '1');
	Position g2(8, 9, '1');
	Position g3(7, 9, '1');
	std::vector<Position> v2 = { g1,g2,g3 };

	Ship sh2(3, v2);

	Gamefield field;
	field.addship(sh1);
	field.addship(sh2);
	field.attacked(1, 1);
	field.attacked(10, 10);
	field.print_field(false);
	return 0;
}