#pragma once
#include "player.h"
#include <string>
class Game {
private:
	Gamefield board1;
	Gamefield board2;
	std::vector<Player> players;
public:
	Game() = default;
	~Game() = default;
	bool input_mode(std::ostream& out, std::istream& in);
	Position input_coords(std::ostream& out,std::istream& in);
	void init_ships(Gamefield& _board,Player& _player, std::ostream& out, std::istream& in);
	void human_init(Gamefield& _board,std::ostream& out, std::istream& in);
	void comp_init(Gamefield& _board, std::ostream& out, std::istream& in);
	void run(std::ostream& out, std::istream& in);
	int move(Player& player,Gamefield& other_board, std::vector<Position> vec, std::ostream& out, std::istream& in);
};
