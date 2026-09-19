#include "ship.h"

Ship::Ship(int _len, std::vector<Position>& _palubs){
	if (_len < 1 || _len > 4) { throw std::logic_error("len from 1 to 4"); }
	if (_palubs.size() != _len) { throw std::logic_error("size != len"); }
	len = _len;
	life = true;
	for (int i = 0;i < _palubs.size();++i) {
		for (int j = 0;j < _palubs.size();++j) {
			if (j == i) { continue; }
			if (_palubs[i].get_x() != _palubs[j].get_x() && _palubs[i].get_y() != _palubs[j].get_y()) {
				throw std::logic_error("No way such ship");
			}
			if (_palubs[i].get_value() != '1') { throw std::logic_error("not ship"); }
		}
	}
	palubs = _palubs;
}

Ship::~Ship() {
	palubs.clear();
	palubs.shrink_to_fit();
}

void Ship::break_palub(int index){
	if (index < 0) { throw std::logic_error("index from 0"); }
	if (index >= palubs.size()) { throw std::logic_error("beyond the limits arr"); }
	palubs[index].set_value('X');
}

bool Ship::isdie()const noexcept {
	for (int i = 0;i < len;++i) {
		if (palubs[i].get_value() == '1') { return false; }
	}
	return true;
}
