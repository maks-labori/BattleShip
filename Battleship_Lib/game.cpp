#include "game.h"

Game::Game() {
	bool mode = input_mode(std::cout,std::cin);
	Player player1(board1, board2, 1);
	Player player2(board2, board1, mode);
	players.push_back(player1);
	players.push_back(player2);
	init_ships(players[0],std::cout , std::cin);
	system("cls");
	init_ships(players[1],std::cout,std::cin);
	system("cls");
}

bool Game::input_mode(std::ostream& out, std::istream& in) {
	std::string str;bool mode;
	while (1) {
		system("cls");
		out << "Choice mode (0 - comp,1 - human): ";
		std::getline(in, str);
		try {
			if(str.size() != 1 || str[0] < '0' || str[0] > '1'){ throw std::logic_error("incorrect input"); }
			mode = (str[0] == '1');
			break;
		}
		catch (std::logic_error& err) {
			out << err.what();
		}
	}
	return mode;
}

void Game::init_ships(Player& _player, std::ostream& out, std::istream& in) {
	if (_player.get_mode()) { human_init(_player,out,in); }
	else { comp_init(_player,out,in); }
}

void Game::human_init(Player& _player, std::ostream& out, std::istream& in) {
	system("cls");
	int i = 0;
	int lens[10] = { 4,3,3,2,2,2,1,1,1,1 };
	while (i < 10) {
		system("cls");
		_player.print_board(true);
		out << "\n\nInput ship (len = " << lens[i] << ") - (advices : A 10 H/V): ";
		try {
			std::string str_x, str_y, str_way;
			in >> str_x >> str_y >> str_way;
			if (str_x.empty()) throw std::logic_error("empty input");
			char letter = std::toupper(str_x[0]);
			if (letter < 'A' || letter > 'J') throw std::logic_error("letter from A to J");
			int x = letter - 'A' + 1;
			int y = std::stoi(str_y);
			if (y < 1 || y > 10) throw std::logic_error("number from 1 to 10");
			if (str_way.empty() || (std::toupper(str_way[0]) != 'H' && std::toupper(str_way[0]) != 'V')) {
				throw std::logic_error("incorrect input,try again");
			}
			int way = (std::toupper(str_way[0]) == 'H'); // H - 1, V - 0
			std::vector<Position> pos;
			pos.push_back(Position(x, y, '1'));
			for (int j = 1;j < lens[i];++j) {
				int new_x = x + (way == 1 ? j : 0);
				int new_y = y + (way == 0 ? j : 0);
				pos.push_back(Position(new_x, new_y, '1'));
				if (new_x > 10 || new_y > 10) { throw std::logic_error("Out behaind of border field"); }
			}
			Ship ship(lens[i], pos);
			if (_player.addship_board(ship)) { i++; }
		}
		catch (std::exception& er) {
			out << er.what();
		}
	}
}

void Game::comp_init(Player& _player, std::ostream& out, std::istream& in) {
	system("cls");
	out << "computer choices ships\n";
	int lens[10] = { 4,3,3,2,2,2,1,1,1,1 };
	int i = 0;
	int attempt = 0;
	while (i < 10) {
		bool out = false;
		std::vector<Position> pos;
		int start_x = rand() % 10 + 1;
		int start_y = rand() % 10 + 1;
		int way = rand() % 2; // 0 - vert , 1 - gorizont;
		pos.push_back(Position(start_x, start_y, '1'));
		for (int j = 1;j < lens[i];++j) {
			int new_x = start_x + (way == 1 ? j : 0);
			int new_y = start_y + (way == 0 ? j : 0);
			if (new_x > 10 || new_y > 10) { out = true;break; }
			pos.push_back(Position(new_x, new_y, '1'));
		}
		if (out) {attempt++;}
		else {
			Ship ship(lens[i], pos);
			if (_player.addship_board(ship)) {i++;continue;}else {attempt++;}
		}
		if (attempt > 300) {i = 0;_player.clear_board();attempt = 0;}
	}
	out << "computer finish choice ships\n";
}

void Game::run(std::ostream& out, std::istream& in) {
	system("cls");
	out << "Start Game\n";
	std::vector<Position> vec;
	while (!players[0].islose() && !players[1].islose()) {
		system("cls");
		if (players[1].get_mode() == 1) { system("pause");system("cls"); }
		out << "First player move\n\n";
		while (move(players[0], players[1], vec,out,in)) { 
			system("cls");
			if (players[1].islose()) {
				out << "First player won";
				break;
			}
		};
		
		if (players[1].get_mode() == 1) { system("pause");system("cls");}
		out << "Second player move\n\n";
		while (move(players[1], players[0], vec,out,in)) { 
			system("cls");
			if (players[0].islose()) {
				out << "Second player won";
				break;
			}
		};
	}
}

int Game::move(Player& player1,Player& player2,std::vector<Position> vec, std::ostream& out, std::istream& in) {
	int total;
	if (player1.get_mode()) {
		player1.print_board(true);
		player2.print_board(false);
		std::vector<int>coords = input_coords(out,in);
		total = player1.human_move(coords[0], coords[1]);
	}
	else {
		total = player1.bot_move(vec);
	}
	return total;
}

std::vector<int> Game::input_coords(std::ostream& out, std::istream& in) {
	std::string str_x;
	std::string str_y;
	while (1) {
		out << "Input coords (advices : A 10): ";
		in >> str_x >> str_y;
		try {
			if (str_x.empty()) throw std::logic_error("empty input");
			char letter = std::toupper(str_x[0]);
			if (letter < 'A' || letter > 'J') {
				throw std::logic_error("letter from A to J");
			}
			int x = letter - 'A' + 1;
			int y = std::stoi(str_y);
			if (y < 1 || y > 10) {
				throw std::logic_error("y from 1 to 10");
			}
			return { x, y };
		}
		catch (std::exception& er) {
			out << "Incorrect input (" << er.what() << "), try again\n";
			in.clear();
		}
	}
}