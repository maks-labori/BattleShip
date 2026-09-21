#pragma once
#include "player.h"
#include <string>
#include <sstream>
class Game {
private:
	Gamefield board1;
	Gamefield board2;
	std::vector<Player> players;
public:
	Game();
	~Game() = default;
	bool input_mode(std::ostream& out, std::istream& in);
	std::vector<int> input_coords(std::ostream& out,std::istream& in);
	void init_ships(Player& _player, std::ostream& out, std::istream& in);
	void human_init(Player& _player, std::ostream& out, std::istream& in);
	void comp_init(Player& _player, std::ostream& out, std::istream& in);
	void run(std::ostream& out, std::istream& in);
	int move(Player& player1, Player& player2, std::vector<Position> vec, std::ostream& out, std::istream& in);
};
