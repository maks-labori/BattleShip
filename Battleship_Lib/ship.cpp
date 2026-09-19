#include "ship.h"

Ship::Ship(int _len, std::vector<Position>& _palubs){
	if (len < 1 || len > 4) { throw std::logic_error("len from 1 to 4"); }
	if (_palubs.size() != _len) { throw std::logic_error("size != len"); }
	
	for (int i = 0;i < palubs.size();++i) {
		for (int j = 0;j < palubs.size();++i) {
			if (j == i) { continue; }
			if (palubs[i].get_x() != palubs[j].get_x() && palubs[i].get_y() != palubs[j].get_y()) {
				throw std::logic_error("No way such ship");
			}
			if (palubs[i].get_value() != '1') { std::logic_error("It is not a ship"); }
		}
	}
	len = _len;
	life = true;
	palubs = _palubs;

}

Ship::~Ship() {
	palubs.clear();
	palubs.shrink_to_fit();
}

void Ship::break_palub(int index) {
	if (index < 0) { throw std::logic_error("index from 0"); }
	if (index >= palubs.size()) { throw std::logic_error("beyond the limits arr"); }
	palubs[index].set_value('X');
}