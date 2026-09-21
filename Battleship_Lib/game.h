#pragma once
#include "player.h"
#include <string>
class Game {
private:
	Gamefield board1;
	Gamefield board2;
	std::vector<Player> players;
public:
	Game();
	~Game() = default;
	bool input_mode();
	std::vector<int> input_coords();
	void init_ships(Player& _player);
	void human_init(Player& _player);
	void comp_init(Player& _player);
	void run();
	int move(Player& player1, Player& player2, std::vector<Position> vec);
};
